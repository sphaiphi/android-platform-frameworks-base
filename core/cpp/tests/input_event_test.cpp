#include <gtest/gtest.h>
#include <android/view/InputEvent.h>
#include <android/view/MotionEvent.h>
#include <android/view/KeyEvent.h>

namespace android::view {

TEST(InputEventWrapperTest, DefaultConstruction) {
    InputEventWrapper wrapper;
    EXPECT_FALSE(wrapper.event.has_value());
    EXPECT_EQ(0u, wrapper.sequence_number);
}

TEST(InputEventWrapperTest, MotionEventConstruction) {
    MotionEvent motion(MotionEvent::ACTION_DOWN, 10.0f, 20.0f);
    InputEventWrapper wrapper(std::move(motion), 42);

    EXPECT_TRUE(wrapper.event.has_value());
    EXPECT_EQ(42u, wrapper.sequence_number);
    EXPECT_TRUE(std::holds_alternative<MotionEvent>(wrapper.event.value()));
    auto& m = std::get<MotionEvent>(wrapper.event.value());
    EXPECT_EQ(10.0f, m.get_x());
    EXPECT_EQ(20.0f, m.get_y());
}

TEST(InputEventWrapperTest, KeyEventConstruction) {
    KeyEvent key(KeyEvent::ACTION_DOWN, 26); // KEYCODE_A
    InputEventWrapper wrapper(std::move(key), 99);

    EXPECT_TRUE(wrapper.event.has_value());
    EXPECT_EQ(99u, wrapper.sequence_number);
    EXPECT_TRUE(std::holds_alternative<KeyEvent>(wrapper.event.value()));
    auto& k = std::get<KeyEvent>(wrapper.event.value());
    EXPECT_EQ(KeyEvent::ACTION_DOWN, k.get_action());
    EXPECT_EQ(26, k.get_key_code());
}

TEST(InputEventWrapperTest, VariantTypeSwitching) {
    InputEventWrapper wrapper;

    // Start empty
    EXPECT_FALSE(wrapper.event.has_value());

    // Switch to MotionEvent
    wrapper.event = MotionEvent(MotionEvent::ACTION_DOWN, 1.0f, 2.0f);
    EXPECT_TRUE(std::holds_alternative<MotionEvent>(wrapper.event.value()));

    // Switch to KeyEvent
    wrapper.event = KeyEvent(KeyEvent::ACTION_UP, 67);
    EXPECT_TRUE(std::holds_alternative<KeyEvent>(wrapper.event.value()));

    // Clear
    wrapper.event = std::nullopt;
    EXPECT_FALSE(wrapper.event.has_value());
}

TEST(MotionEventTest, BasicConstruction) {
    MotionEvent motion(MotionEvent::ACTION_DOWN, 100.0f, 200.0f);
    EXPECT_EQ(MotionEvent::ACTION_DOWN, motion.get_action());
    EXPECT_EQ(100.0f, motion.get_x());
    EXPECT_EQ(200.0f, motion.get_y());
}

TEST(MotionEventTest, FullConstruction) {
    MotionEvent motion(MotionEvent::ACTION_MOVE, 50.0f, 75.0f,
                       1234, 0x00000002, 1000000);
    EXPECT_EQ(MotionEvent::ACTION_MOVE, motion.get_action());
    EXPECT_EQ(50.0f, motion.get_x());
    EXPECT_EQ(75.0f, motion.get_y());
    EXPECT_EQ(1234, motion.get_device_id());
    EXPECT_EQ(0x00000002, motion.get_source());
    EXPECT_EQ(1000000, motion.get_event_time());
}

TEST(MotionEventTest, OffsetLocation) {
    MotionEvent motion(MotionEvent::ACTION_DOWN, 10.0f, 20.0f);
    motion.offset_location(5.0f, 10.0f);
    EXPECT_EQ(15.0f, motion.get_x());
    EXPECT_EQ(30.0f, motion.get_y());
}

TEST(MotionEventTest, HistoryBuffer) {
    MotionEvent motion(MotionEvent::ACTION_DOWN, 10.0f, 20.0f);
    motion.add_history(5.0f, 10.0f, 1);

    EXPECT_EQ(1u, motion.get_history_size());
    auto entry = motion.get_history_entry(0);
    EXPECT_EQ(5.0f, entry.x);
    EXPECT_EQ(10.0f, entry.y);
}

TEST(MotionEventTest, PointerInfo) {
    MotionEvent motion(MotionEvent::ACTION_POINTER_DOWN, 0.0f, 0.0f,
                       0, 0, 0, 2);
    EXPECT_EQ(2u, motion.get_pointer_count());
    EXPECT_EQ(0u, motion.get_pointer_id(0));
    EXPECT_EQ(1u, motion.get_pointer_id(1));
}

TEST(KeyEventTest, BasicConstruction) {
    KeyEvent key(KeyEvent::ACTION_DOWN, 26);
    EXPECT_EQ(KeyEvent::ACTION_DOWN, key.get_action());
    EXPECT_EQ(26, key.get_key_code());
}

TEST(KeyEventTest, FullConstruction) {
    KeyEvent key(KeyEvent::ACTION_UP, 67, 1234, 0x00000100, 2000000, 0, 0);
    EXPECT_EQ(KeyEvent::ACTION_UP, key.get_action());
    EXPECT_EQ(67, key.get_key_code());
    EXPECT_EQ(1234, key.get_device_id());
    EXPECT_EQ(0x00000100, key.get_source());
    EXPECT_EQ(2000000, key.get_event_time());
    EXPECT_EQ(0u, key.get_repeat_count());
    EXPECT_EQ(0u, key.get_meta_state());
}

} // namespace android::view
