#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewGroup.h>
#include <android/view/MotionEvent.h>
#include <android/view/KeyEvent.h>
#include <memory>
#include <vector>

using namespace android::view;

class InputMockView : public View {
public:
    bool touch_event_received = false;
    bool key_event_received = false;
    bool return_value = true;

    bool on_touch_event(const MotionEvent& event) override {
        touch_event_received = true;
        return return_value;
    }

    bool on_key_event(const KeyEvent& event) override {
        key_event_received = true;
        return return_value;
    }
};

TEST(InputTest, TouchEventBubbling) {
    auto parent = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<InputMockView>();
    
    parent->layout(0, 0, 500, 500);
    child->layout(100, 100, 200, 200);
    parent->add_view(child);
    
    // Touch inside child
    MotionEvent event(MotionEvent::ACTION_DOWN, 150, 150);
    EXPECT_TRUE(parent->dispatch_touch_event(event));
    EXPECT_TRUE(child->touch_event_received);
}

TEST(InputTest, TouchEventMiss) {
    auto parent = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<InputMockView>();
    
    parent->layout(0, 0, 500, 500);
    child->layout(100, 100, 200, 200);
    parent->add_view(child);
    
    // Touch outside child but inside parent
    MotionEvent event(MotionEvent::ACTION_DOWN, 50, 50);
    EXPECT_FALSE(parent->dispatch_touch_event(event));
    EXPECT_FALSE(child->touch_event_received);
}

TEST(InputTest, FocusTraversal) {
    auto parent = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto view1 = std::make_shared<InputMockView>();
    auto view2 = std::make_shared<InputMockView>();
    
    parent->add_view(view1);
    parent->add_view(view2);
    
    view1->set_focusable(true);
    view2->set_focusable(true);
    
    EXPECT_FALSE(view1->is_focused());
    EXPECT_FALSE(view2->is_focused());
    
    view1->request_focus();
    EXPECT_TRUE(view1->is_focused());
    EXPECT_FALSE(view2->is_focused());
    
    view2->request_focus();
    EXPECT_FALSE(view1->is_focused());
    EXPECT_TRUE(view2->is_focused());
}
