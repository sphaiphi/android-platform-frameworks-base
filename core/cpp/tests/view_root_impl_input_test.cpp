#include <gtest/gtest.h>
#include <android/view/ViewRootImpl.h>
#include <android/view/View.h>
#include <android/view/MotionEvent.h>
#include <memory>
#include <vector>
#include <string>

namespace android::view {

class InputDispatchMockView : public View {
public:
    std::vector<std::string> calls;
    MotionEvent last_event = MotionEvent(MotionEvent::ACTION_DOWN, 0.0f, 0.0f);

    bool on_touch_event(const MotionEvent& event) override {
        calls.push_back("on_touch_event");
        last_event = event;
        return true;
    }
};

} // namespace android::view

using namespace android::view;

// ── dispatch_pointer_event forwarding ──

TEST(ViewRootImplInputTest, DispatchPointerEventForwardsToRootView) {
    auto view_root = std::make_shared<ViewRootImpl>();
    auto mock_view = std::make_shared<InputDispatchMockView>();
    view_root->set_view(mock_view);

    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 100.0f);
    bool result = view_root->dispatch_pointer_event(event);

    EXPECT_TRUE(result);
    ASSERT_EQ(1u, mock_view->calls.size());
    EXPECT_EQ("on_touch_event", mock_view->calls[0]);
    EXPECT_FLOAT_EQ(50.0f, mock_view->last_event.get_x());
    EXPECT_FLOAT_EQ(100.0f, mock_view->last_event.get_y());
}

TEST(ViewRootImplInputTest, DispatchPointerEventWithMoveAction) {
    auto view_root = std::make_shared<ViewRootImpl>();
    auto mock_view = std::make_shared<InputDispatchMockView>();
    view_root->set_view(mock_view);

    MotionEvent event(MotionEvent::ACTION_MOVE, 75.0f, 125.0f);
    bool result = view_root->dispatch_pointer_event(event);

    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(75.0f, mock_view->last_event.get_x());
    EXPECT_FLOAT_EQ(125.0f, mock_view->last_event.get_y());
}

// ── null view handling ──

TEST(ViewRootImplInputTest, DispatchPointerEventWithNullView) {
    auto view_root = std::make_shared<ViewRootImpl>();
    // No view set

    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 100.0f);
    bool result = view_root->dispatch_pointer_event(event);

    EXPECT_FALSE(result);
}

TEST(ViewRootImplInputTest, DispatchPointerEventAfterViewCleared) {
    auto view_root = std::make_shared<ViewRootImpl>();
    view_root->set_view(std::make_shared<InputDispatchMockView>());
    view_root->set_view(nullptr);

    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 100.0f);
    bool result = view_root->dispatch_pointer_event(event);

    EXPECT_FALSE(result);
}
