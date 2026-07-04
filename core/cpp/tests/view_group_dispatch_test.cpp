#include <gtest/gtest.h>
#include <android/view/ViewGroup.h>
#include <android/view/View.h>
#include <android/view/MotionEvent.h>
#include <memory>

namespace android::view {

// ── Custom view that tracks touch event delivery ──

class TouchTrackingView : public View {
public:
    bool touch_event_received = false;
    MotionEvent last_event = MotionEvent(MotionEvent::ACTION_DOWN, 0.0f, 0.0f);

    bool on_touch_event(const MotionEvent& event) override {
        touch_event_received = true;
        last_event = event;
        return true;
    }
};

// ── Custom ViewGroup that can intercept ──

class InterceptingViewGroup : public ViewGroup<MarginLayoutParams> {
public:
    bool intercept = false;
    bool touch_event_received = false;
    MotionEvent last_event = MotionEvent(MotionEvent::ACTION_DOWN, 0.0f, 0.0f);

    bool on_intercept_touch_event(const MotionEvent& /*event*/) override {
        return intercept;
    }

    bool on_touch_event(const MotionEvent& event) override {
        touch_event_received = true;
        last_event = event;
        return true;
    }
};

// ── Hit-testing within child bounds ──

TEST(ViewGroupDispatchTest, HitTestWithinChildBounds) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(10, 10, 110, 110);
    group->add_view(child);

    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 50.0f);
    bool result = group->dispatch_pointer_event(event);

    EXPECT_TRUE(result);
    EXPECT_TRUE(child->touch_event_received);
}

TEST(ViewGroupDispatchTest, HitTestOutsideChildBounds) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(10, 10, 110, 110);
    group->add_view(child);

    MotionEvent event(MotionEvent::ACTION_DOWN, 5.0f, 5.0f);
    bool result = group->dispatch_pointer_event(event);

    EXPECT_FALSE(result);
    EXPECT_FALSE(child->touch_event_received);
}

TEST(ViewGroupDispatchTest, HitTestOnChildEdge) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(50, 50, 150, 150);
    group->add_view(child);

    // On the left edge (inclusive)
    MotionEvent eventLeft(MotionEvent::ACTION_DOWN, 50.0f, 75.0f);
    EXPECT_TRUE(group->dispatch_pointer_event(eventLeft));
    EXPECT_TRUE(child->touch_event_received);

    child->touch_event_received = false;

    // Just outside the right edge (exclusive)
    MotionEvent eventRight(MotionEvent::ACTION_DOWN, 150.0f, 75.0f);
    EXPECT_FALSE(group->dispatch_pointer_event(eventRight));
    EXPECT_FALSE(child->touch_event_received);
}

// ── Coordinate transformation to local space ──

TEST(ViewGroupDispatchTest, CoordinateTransformationToLocalSpace) {
    auto group = std::make_shared<InterceptingViewGroup>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(30, 40, 130, 140);
    group->add_view(child);

    MotionEvent event(MotionEvent::ACTION_DOWN, 80.0f, 90.0f);
    group->dispatch_pointer_event(event);

    // Child should receive event with coordinates transformed to its local space
    // Global (80, 90) - child offset (30, 40) = local (50, 50)
    EXPECT_FLOAT_EQ(50.0f, child->last_event.get_x());
    EXPECT_FLOAT_EQ(50.0f, child->last_event.get_y());
}

// ── Event interception ──

TEST(ViewGroupDispatchTest, EventInterceptionPreventsChildDelivery) {
    auto group = std::make_shared<InterceptingViewGroup>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(10, 10, 110, 110);
    group->add_view(child);

    group->intercept = true;
    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 50.0f);
    bool result = group->dispatch_pointer_event(event);

    EXPECT_TRUE(result);
    EXPECT_TRUE(group->touch_event_received);
    EXPECT_FALSE(child->touch_event_received);
}

TEST(ViewGroupDispatchTest, NoInterceptionAllowsChildDelivery) {
    auto group = std::make_shared<InterceptingViewGroup>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(10, 10, 110, 110);
    group->add_view(child);

    group->intercept = false;
    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 50.0f);
    bool result = group->dispatch_pointer_event(event);

    EXPECT_TRUE(result);
    EXPECT_FALSE(group->touch_event_received);
    EXPECT_TRUE(child->touch_event_received);
}

// ── Reverse Z-order iteration (top-most first) ──

TEST(ViewGroupDispatchTest, ReverseZOrderTopMostFirst) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto bottom = std::make_shared<TouchTrackingView>();
    auto top = std::make_shared<TouchTrackingView>();

    bottom->layout(0, 0, 200, 200);
    top->layout(0, 0, 200, 200);

    group->add_view(bottom); // added first = bottom layer
    group->add_view(top);    // added second = top layer

    MotionEvent event(MotionEvent::ACTION_DOWN, 100.0f, 100.0f);
    bool result = group->dispatch_pointer_event(event);

    // Top view should receive the event first and handle it
    EXPECT_TRUE(result);
    EXPECT_TRUE(top->touch_event_received);
    EXPECT_FALSE(bottom->touch_event_received);
}

TEST(ViewGroupDispatchTest, TopViewRejectsThenBottomReceives) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto bottom = std::make_shared<TouchTrackingView>();
    auto top = std::make_shared<TouchTrackingView>();

    bottom->layout(0, 0, 200, 200);
    top->layout(0, 0, 100, 100); // smaller, covers only top-left

    group->add_view(bottom);
    group->add_view(top);

    // Point in top view's area — top gets it
    MotionEvent event1(MotionEvent::ACTION_DOWN, 50.0f, 50.0f);
    EXPECT_TRUE(group->dispatch_pointer_event(event1));
    EXPECT_TRUE(top->touch_event_received);

    top->touch_event_received = false;
    bottom->touch_event_received = false;

    // Point outside top view but inside bottom — bottom gets it
    MotionEvent event2(MotionEvent::ACTION_DOWN, 150.0f, 150.0f);
    EXPECT_TRUE(group->dispatch_pointer_event(event2));
    EXPECT_FALSE(top->touch_event_received);
    EXPECT_TRUE(bottom->touch_event_received);
}

// ── Nested hierarchy recursion ──

TEST(ViewGroupDispatchTest, NestedHierarchyRecursion) {
    auto root = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto middle = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto leaf = std::make_shared<TouchTrackingView>();

    middle->layout(0, 0, 200, 200);
    leaf->layout(50, 50, 150, 150);

    middle->add_view(leaf);
    root->add_view(middle);

    MotionEvent event(MotionEvent::ACTION_DOWN, 100.0f, 100.0f);
    bool result = root->dispatch_pointer_event(event);

    EXPECT_TRUE(result);
    EXPECT_TRUE(leaf->touch_event_received);
    // Coordinates: global (100,100) -> middle local (100,100) -> leaf local (50,50)
    EXPECT_FLOAT_EQ(50.0f, leaf->last_event.get_x());
    EXPECT_FLOAT_EQ(50.0f, leaf->last_event.get_y());
}

TEST(ViewGroupDispatchTest, NestedHierarchyInvisibleChildSkipped) {
    auto root = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<TouchTrackingView>();
    child->layout(0, 0, 200, 200);
    child->set_visibility(Visibility::Invisible);
    root->add_view(child);

    MotionEvent event(MotionEvent::ACTION_DOWN, 100.0f, 100.0f);
    bool result = root->dispatch_pointer_event(event);

    EXPECT_FALSE(result);
    EXPECT_FALSE(child->touch_event_received);
}

// ── Event bubbling when no child handles ──

TEST(ViewGroupDispatchTest, EventBubblingWhenNoChildHandles) {
    // Use plain View (on_touch_event returns false by default)
    auto group = std::make_shared<InterceptingViewGroup>();
    auto child = std::make_shared<View>(); // default on_touch_event returns false
    child->layout(10, 10, 110, 110);
    group->add_view(child);

    MotionEvent event(MotionEvent::ACTION_DOWN, 50.0f, 50.0f);
    bool result = group->dispatch_pointer_event(event);

    // Child doesn't handle, so group's on_touch_event is called
    // InterceptingViewGroup's on_touch_event returns true
    EXPECT_TRUE(result);
    EXPECT_TRUE(group->touch_event_received);
}

// ── get_children accessor ──

TEST(ViewGroupDispatchTest, GetChildrenAccessor) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();
    group->add_view(child1);
    group->add_view(child2);

    const auto& children = group->get_children();
    EXPECT_EQ(2u, children.size());
    EXPECT_EQ(child1, children[0]);
    EXPECT_EQ(child2, children[1]);
}

// ── bounds_overlap helper ──

TEST(ViewGroupDispatchTest, BoundsOverlapTrue) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    group->layout(10, 20, 110, 120);

    EXPECT_TRUE(group->bounds_overlap(50.0f, 50.0f));
    EXPECT_TRUE(group->bounds_overlap(10.0f, 20.0f));
}

TEST(ViewGroupDispatchTest, BoundsOverlapFalse) {
    auto group = std::make_shared<ViewGroup<MarginLayoutParams>>();
    group->layout(10, 20, 110, 120);

    EXPECT_FALSE(group->bounds_overlap(5.0f, 50.0f));   // left of bounds
    EXPECT_FALSE(group->bounds_overlap(110.0f, 50.0f)); // right edge (exclusive)
    EXPECT_FALSE(group->bounds_overlap(50.0f, 5.0f));   // above bounds
    EXPECT_FALSE(group->bounds_overlap(50.0f, 120.0f)); // bottom edge (exclusive)
}

} // namespace android::view
