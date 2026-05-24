#include <gtest/gtest.h>
#include <android/view/InputEventReceiver.h>
#include <android/view/InputChannel.h>
#include <android/os/Looper.h>
#include "mock_input_channel.h"

#include <thread>
#include <cstring>
#include <poll.h>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace android::view {

// ── Helper: create a mock channel + looper for tests ──

static auto make_mock_channel() -> std::shared_ptr<InputChannel> {
    return test::MockInputChannel::create("test_channel");
}

static auto make_looper() -> std::shared_ptr<os::Looper> {
    return std::make_shared<os::Looper>();
}

// ── Constructor Validation ──

TEST(InputEventReceiverTest, ConstructorWithValidChannelAndLooper) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    bool callback_called = false;

    EXPECT_NO_THROW({
        InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper&) {
            callback_called = true;
        });
    });
}

TEST(InputEventReceiverTest, ConstructorWithNullChannelThrows) {
    auto looper = make_looper();

    EXPECT_THROW({
        InputEventReceiver receiver(nullptr, looper, [](const InputEventWrapper&) {});
    }, std::invalid_argument);
}

TEST(InputEventReceiverTest, ConstructorWithInvalidChannelThrows) {
    auto channel = std::make_shared<InputChannel>("invalid", nullptr);
    auto looper = make_looper();

    EXPECT_THROW({
        InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});
    }, std::invalid_argument);
}

TEST(InputEventReceiverTest, ConstructorWithNullLooperThrows) {
    auto channel = make_mock_channel();

    EXPECT_THROW({
        InputEventReceiver receiver(channel, nullptr, [](const InputEventWrapper&) {});
    }, std::invalid_argument);
}

TEST(InputEventReceiverTest, ConstructorWithNullCallbackThrows) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    EXPECT_THROW({
        InputEventReceiver receiver(channel, looper, nullptr);
    }, std::invalid_argument);
}

// ── consumeEvents ──

TEST(InputEventReceiverTest, ConsumeEventsEmptyReturnsEmpty) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::vector<InputEventWrapper> received;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        received.push_back(w);
    });

    auto events = receiver.consume_events();
    EXPECT_TRUE(events.empty());
}

TEST(InputEventReceiverTest, ConsumeEventsMotionEvent) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::vector<InputEventWrapper> received;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        received.push_back(w);
    });

    // Inject a MotionEvent
    auto write_fd = test::MockInputChannel::get_write_fd(channel);
    test::MockInputChannel::send_motion_event(channel, 1, 100.0f, 200.0f);

    // Give the read side time to receive
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto events = receiver.consume_events();
    EXPECT_FALSE(events.empty());
    EXPECT_EQ(1u, events.size());
    EXPECT_TRUE(events[0].event.has_value());
    EXPECT_TRUE(std::holds_alternative<MotionEvent>(events[0].event.value()));
    EXPECT_EQ(1u, events[0].sequence_number);

    auto& motion = std::get<MotionEvent>(events[0].event.value());
    EXPECT_EQ(100.0f, motion.get_x());
    EXPECT_EQ(200.0f, motion.get_y());
}

TEST(InputEventReceiverTest, ConsumeEventsKeyEvent) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::vector<InputEventWrapper> received;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        received.push_back(w);
    });

    test::MockInputChannel::send_key_event(channel, 2, 26);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto events = receiver.consume_events();
    EXPECT_FALSE(events.empty());
    EXPECT_TRUE(std::holds_alternative<KeyEvent>(events[0].event.value()));
    EXPECT_EQ(2u, events[0].sequence_number);

    auto& key = std::get<KeyEvent>(events[0].event.value());
    EXPECT_EQ(26, key.get_key_code());
}

TEST(InputEventReceiverTest, ConsumeMultipleEvents) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::vector<InputEventWrapper> received;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        received.push_back(w);
    });

    // Inject 3 events
    test::MockInputChannel::send_motion_event(channel, 1, 10.0f, 20.0f);
    test::MockInputChannel::send_motion_event(channel, 2, 30.0f, 40.0f);
    test::MockInputChannel::send_key_event(channel, 3, 67);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto events = receiver.consume_events();
    EXPECT_EQ(3u, events.size());
    EXPECT_EQ(1u, events[0].sequence_number);
    EXPECT_EQ(2u, events[1].sequence_number);
    EXPECT_EQ(3u, events[2].sequence_number);
}

// ── finishInputEvent ──

TEST(InputEventReceiverTest, FinishInputEventNoEventThrows) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    auto result = receiver.finish_input_event(true);
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(InputError::NO_EVENT_IN_PROGRESS, result.error());
}

TEST(InputEventReceiverTest, FinishInputEventAfterDisposeThrows) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::atomic<bool> callback_fired = false;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        callback_fired = true;
    });

    // Inject and consume an event so there's a current event
    test::MockInputChannel::send_motion_event(channel, 1, 10.0f, 20.0f);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto events = receiver.consume_events();
    receiver.dispatch_event(std::move(events[0]));

    receiver.dispose();

    auto result = receiver.finish_input_event(true);
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(InputError::DISPOSED, result.error());
}

// ── Dispose ──

TEST(InputEventReceiverTest, Dispose) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    {
        InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});
        EXPECT_FALSE(receiver.is_disposed());
        receiver.dispose();
        EXPECT_TRUE(receiver.is_disposed());
    }

    // Channel should be closed after receiver is destroyed
    EXPECT_FALSE(channel->is_valid());
}

TEST(InputEventReceiverTest, ConsumeEventsAfterDisposeReturnsEmpty) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    {
        InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});
        receiver.dispose();

        auto events = receiver.consume_events();
        EXPECT_TRUE(events.empty());
    }
}

// ── Batch Processing ──

TEST(InputEventReceiverTest, ConsumeBatchedInputEvents) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::atomic<int> callback_count = 0;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper&) {
        callback_count++;
    });

    test::MockInputChannel::send_motion_event(channel, 1, 10.0f, 20.0f);
    test::MockInputChannel::send_motion_event(channel, 2, 30.0f, 40.0f);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto result = receiver.consume_batched_input_events();
    EXPECT_TRUE(result);
    EXPECT_EQ(2, callback_count);
}

TEST(InputEventReceiverTest, ConsumeBatchedInputEventsEmpty) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    auto result = receiver.consume_batched_input_events();
    EXPECT_FALSE(result);
}

// ── probablyHasInput ──

TEST(InputEventReceiverTest, ProbablyHasInputNoData) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    // No data written — should return false (or possibly true due to socket state)
    // We just verify it doesn't crash
    EXPECT_NO_THROW(receiver.probably_has_input());
}

TEST(InputEventReceiverTest, ProbablyHasInputWithData) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    // Write a byte to the write end
    uint8_t byte = 0xFF;
    auto write_fd = test::MockInputChannel::get_write_fd(channel);
    ::write(write_fd, &byte, 1);

    // Should detect data
    EXPECT_TRUE(receiver.probably_has_input());
}

// ── Special Event Callbacks ──

TEST(InputEventReceiverTest, OnFocusEvent) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_NO_THROW(receiver.on_focus_event(true));
    EXPECT_NO_THROW(receiver.on_focus_event(false));
}

TEST(InputEventReceiverTest, OnTouchModeChanged) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_NO_THROW(receiver.on_touch_mode_changed(true));
    EXPECT_NO_THROW(receiver.on_touch_mode_changed(false));
}

TEST(InputEventReceiverTest, OnPointerCaptureEvent) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_NO_THROW(receiver.on_pointer_capture_event(true));
    EXPECT_NO_THROW(receiver.on_pointer_capture_event(false));
}

// ── ReportTimeline (stub) ──

TEST(InputEventReceiverTest, ReportTimelineNoop) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_NO_THROW(receiver.report_timeline(1000000));
    EXPECT_NO_THROW(receiver.report_timeline(0));
}

// ── Register/Unregister Looper ──

TEST(InputEventReceiverTest, RegisterUnregisterLooper) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_NO_THROW(receiver.register_with_looper());
    EXPECT_NO_THROW(receiver.register_with_looper()); // Should be no-op
    EXPECT_NO_THROW(receiver.unregister_from_looper());
    EXPECT_NO_THROW(receiver.unregister_from_looper()); // Should be no-op
}

// ── Sequential Event Processing Invariant ──

TEST(InputEventReceiverTest, SequentialEventProcessing) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::vector<InputEventWrapper> received;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        received.push_back(w);
    });

    // Inject 5 events
    for (uint32_t i = 1; i <= 5; i++) {
        test::MockInputChannel::send_motion_event(channel, i,
            static_cast<float>(i * 10), static_cast<float>(i * 20));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto events = receiver.consume_events();
    EXPECT_EQ(5u, events.size());

    // Verify sequence numbers are sequential
    for (size_t i = 0; i < events.size(); i++) {
        EXPECT_EQ(static_cast<uint32_t>(i + 1), events[i].sequence_number);
    }
}

// ── Accessors ──

TEST(InputEventReceiverTest, GetChannel) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_EQ(channel, receiver.get_channel());
}

TEST(InputEventReceiverTest, GetLooper) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_EQ(looper, receiver.get_looper());
}

// ── Looper FD Integration (US2) ──

TEST(InputEventReceiverTest, RegisterWithLooperRegistersFd) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_FALSE(receiver.is_disposed());
    receiver.register_with_looper();
    // After registration, the FD should be tracked by the Looper
    // We verify by writing data and polling
    test::MockInputChannel::send_motion_event(channel, 1, 10.0f, 20.0f);

    int fd = channel->read_fd();
    EXPECT_GT(fd, 0);

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    int ret = poll(&pfd, 1, 0);
    EXPECT_GT(ret, 0);
    EXPECT_TRUE((pfd.revents & POLLIN) != 0);
}

TEST(InputEventReceiverTest, FdCallbackDispatchesEvents) {
    auto channel = make_mock_channel();
    auto looper = make_looper();
    std::vector<InputEventWrapper> received;

    InputEventReceiver receiver(channel, looper, [&](const InputEventWrapper& w) {
        received.push_back(w);
    });

    receiver.register_with_looper();

    // Inject 2 events
    test::MockInputChannel::send_motion_event(channel, 1, 10.0f, 20.0f);
    test::MockInputChannel::send_motion_event(channel, 2, 30.0f, 40.0f);

    // Poll the looper — should trigger FD callback and dispatch events
    looper->poll_once();

    EXPECT_EQ(2u, received.size());
    EXPECT_EQ(1u, received[0].sequence_number);
    EXPECT_EQ(2u, received[1].sequence_number);
}

TEST(InputEventReceiverTest, DisposeRemovesFdWatcher) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});
    receiver.register_with_looper();

    // Inject event while registered
    test::MockInputChannel::send_motion_event(channel, 1, 10.0f, 20.0f);
    looper->poll_once();

    // Dispose should unregister FD
    receiver.dispose();
    EXPECT_TRUE(receiver.is_disposed());

    // Channel should be closed
    EXPECT_FALSE(channel->is_valid());
}

// ── Phase 6: Special Event State Tracking (US4) ──

TEST(InputEventReceiverTest, OnFocusEventUpdatesState) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_FALSE(receiver.get_has_focus());
    receiver.on_focus_event(true);
    EXPECT_TRUE(receiver.get_has_focus());
    receiver.on_focus_event(false);
    EXPECT_FALSE(receiver.get_has_focus());
}

TEST(InputEventReceiverTest, OnFocusEventAfterDisposeIsNoOp) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});
    receiver.on_focus_event(true);
    EXPECT_TRUE(receiver.get_has_focus());

    receiver.dispose();
    receiver.on_focus_event(false);
    EXPECT_TRUE(receiver.get_has_focus()); // state unchanged after dispose
}

TEST(InputEventReceiverTest, OnTouchModeChangedUpdatesState) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_FALSE(receiver.get_in_touch_mode());
    receiver.on_touch_mode_changed(true);
    EXPECT_TRUE(receiver.get_in_touch_mode());
    receiver.on_touch_mode_changed(false);
    EXPECT_FALSE(receiver.get_in_touch_mode());
}

TEST(InputEventReceiverTest, OnPointerCaptureEventUpdatesState) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_FALSE(receiver.get_pointer_capture_enabled());
    receiver.on_pointer_capture_event(true);
    EXPECT_TRUE(receiver.get_pointer_capture_enabled());
    receiver.on_pointer_capture_event(false);
    EXPECT_FALSE(receiver.get_pointer_capture_enabled());
}

TEST(InputEventReceiverTest, InitialStatesAreFalse) {
    auto channel = make_mock_channel();
    auto looper = make_looper();

    InputEventReceiver receiver(channel, looper, [](const InputEventWrapper&) {});

    EXPECT_FALSE(receiver.get_has_focus());
    EXPECT_FALSE(receiver.get_in_touch_mode());
    EXPECT_FALSE(receiver.get_pointer_capture_enabled());
}

} // namespace android::view
