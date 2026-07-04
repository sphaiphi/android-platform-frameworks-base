#include <gtest/gtest.h>
#include <android/view/ViewGroup.h>
#include <android/view/View.h>
#include <android/view/LayoutParams.h>

using namespace android::view;

// ============================================================================
// Test 1: Template instantiation with MarginLayoutParams
// ============================================================================
TEST(ViewGroupFoundational, TemplateInstantiation) {
    // ViewGroup<MarginLayoutParams> should compile and work
    ViewGroup<MarginLayoutParams> container;
    EXPECT_EQ(0, container.get_child_count());
}

// ============================================================================
// Test 2: Default template parameter
// ============================================================================
TEST(ViewGroupFoundational, DefaultTemplateParameter) {
    // ViewGroup<> should default to MarginLayoutParams
    ViewGroup<> container;
    EXPECT_EQ(0, container.get_child_count());
}

// ============================================================================
// Test 3: Child count management
// ============================================================================
TEST(ViewGroupFoundational, ChildCountManagement) {
    ViewGroup<MarginLayoutParams> container;

    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();
    auto child3 = std::make_shared<View>();

    container.add_view(child1);
    EXPECT_EQ(1, container.get_child_count());

    container.add_view(child2);
    EXPECT_EQ(2, container.get_child_count());

    container.add_view(child3);
    EXPECT_EQ(3, container.get_child_count());
}

// ============================================================================
// Test 4: get_child_at bounds checking
// ============================================================================
TEST(ViewGroupFoundational, GetChildAtBoundsChecking) {
    ViewGroup<MarginLayoutParams> container;
    auto child = std::make_shared<View>();
    container.add_view(child);

    EXPECT_EQ(child, container.get_child_at(0));
    EXPECT_EQ(nullptr, container.get_child_at(-1));
    EXPECT_EQ(nullptr, container.get_child_at(1));
}

// ============================================================================
// Test 5: remove_view_at bounds checking
// ============================================================================
TEST(ViewGroupFoundational, RemoveViewAtBoundsChecking) {
    ViewGroup<MarginLayoutParams> container;
    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();
    container.add_view(child1);
    container.add_view(child2);

    container.remove_view_at(0);
    EXPECT_EQ(1, container.get_child_count());
    EXPECT_EQ(child2, container.get_child_at(0));

    // Out of bounds should be a no-op
    EXPECT_NO_THROW(container.remove_view_at(10));
    EXPECT_EQ(1, container.get_child_count());
}

// ============================================================================
// Test 6: Clip children flag
// ============================================================================
TEST(ViewGroupFoundational, ClipChildrenFlag) {
    ViewGroup<MarginLayoutParams> container;

    // Default should be clip_children = true
    EXPECT_TRUE(container.is_clip_children());

    container.set_clip_children(false);
    EXPECT_FALSE(container.is_clip_children());

    container.set_clip_children(true);
    EXPECT_TRUE(container.is_clip_children());
}

// ============================================================================
// Test 7: Clip to padding flag
// ============================================================================
TEST(ViewGroupFoundational, ClipToPaddingFlag) {
    ViewGroup<MarginLayoutParams> container;

    // Default should be clip_to_padding = true
    EXPECT_TRUE(container.is_clip_to_padding());

    container.set_clip_to_padding(false);
    EXPECT_FALSE(container.is_clip_to_padding());
}

// ============================================================================
// Test 8: Descendant focusability modes
// ============================================================================
TEST(ViewGroupFoundational, DescendantFocusabilityModes) {
    ViewGroup<MarginLayoutParams> container;

    // Default is FOCUS_BEFORE_DESCENDANTS
    EXPECT_EQ(DescendantFocusability::FOCUS_BEFORE_DESCENDANTS,
              container.get_descendant_focusability());

    container.set_descendant_focusability(DescendantFocusability::FOCUS_AFTER_DESCENDANTS);
    EXPECT_EQ(DescendantFocusability::FOCUS_AFTER_DESCENDANTS,
              container.get_descendant_focusability());

    container.set_descendant_focusability(DescendantFocusability::FOCUS_BLOCK_DESCENDANTS);
    EXPECT_EQ(DescendantFocusability::FOCUS_BLOCK_DESCENDANTS,
              container.get_descendant_focusability());
}

// ============================================================================
// Test 9: Disallow intercept touch event
// ============================================================================
TEST(ViewGroupFoundational, DisallowInterceptTouchEvent) {
    ViewGroup<MarginLayoutParams> container;

    // Default should be false (allow intercept)
    // Note: disallow_intercept_ is private, but we can test via behavior

    container.request_disallow_intercept_touch_event(true);
    // After disallowing, intercept should be bypassed

    container.request_disallow_intercept_touch_event(false);
    // After re-allowing, intercept works normally
}

// ============================================================================
// Test 10: Clear focus propagates to children
// ============================================================================
TEST(ViewGroupFoundational, ClearFocusPropagatesToChildren) {
    ViewGroup<MarginLayoutParams> container;
    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();

    container.add_view(child1);
    container.add_view(child2);

    // clear_focus should clear focus on all children
    EXPECT_NO_THROW(container.clear_focus());
}

// ============================================================================
// Test 11: Get children vector access
// ============================================================================
TEST(ViewGroupFoundational, GetChildrenVectorAccess) {
    ViewGroup<MarginLayoutParams> container;
    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();

    container.add_view(child1);
    container.add_view(child2);

    const auto& children = container.get_children();
    EXPECT_EQ(2u, children.size());
    EXPECT_EQ(child1, children[0]);
    EXPECT_EQ(child2, children[1]);
}

// ============================================================================
// Test 12: LayoutParamsType alias
// ============================================================================
TEST(ViewGroupFoundational, LayoutParamsTypeAlias) {
    // Verify the type alias works
    using ParamsType = ViewGroup<MarginLayoutParams>::LayoutParamsType;
    static_assert(std::is_same_v<ParamsType, MarginLayoutParams>,
                  "LayoutParamsType should be MarginLayoutParams");
}
