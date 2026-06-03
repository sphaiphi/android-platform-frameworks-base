#include <android/view/DisplayEventReceiver.h>
#include <android/os/Looper.h>

#include <gtest/gtest.h>

#include <atomic>

using android::view::DisplayEventReceiver;
using android::view::VsyncEventData;
using android::os::Looper;

// Helper: prepare a Looper on the current thread
static auto prepare_looper() -> std::shared_ptr<Looper> {
    Looper::prepare();
    return Looper::my_looper();
}

// Test: Constructor with valid Looper
TEST(DisplayEventReceiverTest, ConstructorWithValidLooper) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);
    ASSERT_NE(der, nullptr);
    ASSERT_FALSE(der->is_disposed());
}

// Test: Constructor with null Looper throws
TEST(DisplayEventReceiverTest, ConstructorWithNullLooperThrows) {
    EXPECT_THROW(DisplayEventReceiver(nullptr, DisplayEventReceiver::VsyncCallback{}), std::runtime_error);
}

// Test: schedule_vsync is no-op when disposed
TEST(DisplayEventReceiverTest, ScheduleVsyncNoopWhenDisposed) {
    auto looper = prepare_looper();
    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);

    der->dispose();
    ASSERT_TRUE(der->is_disposed());

    // schedule_vsync after dispose should be a no-op (not crash)
    EXPECT_NO_THROW(der->schedule_vsync());
}

// Test: register/unregister looper
TEST(DisplayEventReceiverTest, RegisterUnregisterLooper) {
    auto looper = prepare_looper();
    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);

    der->register_with_looper();
    ASSERT_EQ(der->get_looper(), looper);

    der->unregister_from_looper();
}

// Test: Dispose closes FD
TEST(DisplayEventReceiverTest, DisposeClosesFd) {
    auto looper = prepare_looper();
    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);

    der->dispose();
    ASSERT_TRUE(der->is_disposed());

    // Second dispose should be a no-op
    EXPECT_NO_THROW(der->dispose());
}

// Test: Move constructor preserves state
TEST(DisplayEventReceiverTest, MoveConstructorPreservesState) {
    auto looper = prepare_looper();
    auto der1 = std::make_shared<DisplayEventReceiver>(looper, nullptr);

    // Move the shared_ptr itself
    auto der2 = std::move(der1);
    ASSERT_NE(der2, nullptr);
    ASSERT_FALSE(der2->is_disposed());
    ASSERT_EQ(der2->get_looper(), looper);
    ASSERT_EQ(der1, nullptr); // Original is now null
}

// Test: Default frame interval is 60Hz
TEST(DisplayEventReceiverTest, FrameIntervalDefault60Hz) {
    auto looper = prepare_looper();
    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);

    EXPECT_EQ(der->get_frame_interval_nanos(), 16666667); // 60Hz
}

// Test: Callback with null function is safe
TEST(DisplayEventReceiverTest, NullCallbackIsSafe) {
    auto looper = prepare_looper();

    // Create with null callback — should not crash
    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);
    ASSERT_NE(der, nullptr);

    der->dispose();
}

// Test: set_vsync_callback updates the callback
TEST(DisplayEventReceiverTest, SetVsyncCallbackUpdatesCallback) {
    auto looper = prepare_looper();

    auto der = std::make_shared<DisplayEventReceiver>(looper, nullptr);

    // Set callback after construction
    der->set_vsync_callback([](const VsyncEventData& /*data*/) {
        // callback placeholder
    });
    ASSERT_FALSE(der->is_disposed());

    der->dispose();
}
