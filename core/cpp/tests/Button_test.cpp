#include <gtest/gtest.h>
#include <android/widget/Button.h>
#include <android/view/MotionEvent.h>
#include <memory>

using namespace android::view;
using namespace android::widget;

class MockClickListener {
public:
    bool clicked{false};
    void onClick(View* /*v*/) { clicked = true; }
};

TEST(ButtonTest, ClickListener) {
    auto button = std::make_shared<Button>();
    MockClickListener listener;
    
    // In our implementation, we'll use a simplified lambda-based click listener for now
    bool clicked = false;
    button->set_on_click_listener([&clicked](View* /*v*/) { clicked = true; });
    
    // Simulate a click sequence: Down then Up
    MotionEvent downEvent(MotionEvent::ACTION_DOWN, 10.0f, 10.0f);
    button->on_touch_event(downEvent);
    
    EXPECT_FALSE(clicked);
    
    MotionEvent upEvent(MotionEvent::ACTION_UP, 10.0f, 10.0f);
    button->on_touch_event(upEvent);
    
    EXPECT_TRUE(clicked);
}
