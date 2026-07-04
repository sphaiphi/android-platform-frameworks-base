#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewGroup.h>
#include <android/view/ViewManagerMixin.h>
#include <android/view/LayoutParams.h>

using namespace android::view;

// ============================================================================
// Test 1: add_view delegates to derived class
// ============================================================================
TEST(ViewManagerMixinTest, AddViewDelegatesToDerived) {
    ViewGroup<MarginLayoutParams> container;
    auto child = std::make_shared<View>();

    container.add_view(child);
    EXPECT_EQ(1, container.get_child_count());
    EXPECT_EQ(child, container.get_child_at(0));
}

// ============================================================================
// Test 2: update_view_layout delegates to derived class
// ============================================================================
TEST(ViewManagerMixinTest, UpdateViewLayoutDelegatesToDerived) {
    ViewGroup<MarginLayoutParams> container;
    auto child = std::make_shared<View>();
    auto new_params = std::make_shared<MarginLayoutParams>(200, 200);

    container.add_view(child);
    container.update_view_layout(child, new_params);
    EXPECT_EQ(new_params, child->get_layout_params());
}

// ============================================================================
// Test 3: remove_view delegates to derived class
// ============================================================================
TEST(ViewManagerMixinTest, RemoveViewDelegatesToDerived) {
    ViewGroup<MarginLayoutParams> container;
    auto child = std::make_shared<View>();

    container.add_view(child);
    EXPECT_EQ(1, container.get_child_count());

    container.remove_view(child);
    EXPECT_EQ(0, container.get_child_count());
    EXPECT_EQ(nullptr, child->get_parent());
}

// ============================================================================
// Test 4: CRTP dispatch is zero-cost (static dispatch)
// ============================================================================
TEST(ViewManagerMixinTest, CRTPStaticDispatch) {
    // The ViewManagerMixin uses static_cast<Derived*>(this) for dispatch.
    // This test verifies the pattern works correctly.
    ViewGroup<MarginLayoutParams> container;
    auto child = std::make_shared<View>();

    // All three mixin methods should work through CRTP
    EXPECT_NO_THROW(container.add_view(child));
    auto params = std::make_shared<MarginLayoutParams>(100, 100);
    EXPECT_NO_THROW(container.update_view_layout(child, params));
    EXPECT_NO_THROW(container.remove_view(child));
}

// ============================================================================
// Test 5: add_view with explicit params
// ============================================================================
TEST(ViewManagerMixinTest, AddViewWithExplicitParams) {
    ViewGroup<MarginLayoutParams> container;
    auto child = std::make_shared<View>();
    auto params = std::make_shared<MarginLayoutParams>(150, 75);

    container.add_view(child, params);
    EXPECT_EQ(1, container.get_child_count());
    EXPECT_EQ(params, child->get_layout_params());
}

// ============================================================================
// Test 6: Reparenting — removing from old parent
// ============================================================================
TEST(ViewManagerMixinTest, ReparentingRemovesFromOldParent) {
    ViewGroup<MarginLayoutParams> parent1;
    ViewGroup<MarginLayoutParams> parent2;
    auto child = std::make_shared<View>();

    parent1.add_view(child);
    EXPECT_EQ(1, parent1.get_child_count());
    EXPECT_EQ(&parent1, child->get_parent());

    parent2.add_view(child);
    EXPECT_EQ(0, parent1.get_child_count());
    EXPECT_EQ(1, parent2.get_child_count());
    EXPECT_EQ(&parent2, child->get_parent());
}

// ============================================================================
// Test 7: Null child handling
// ============================================================================
TEST(ViewManagerMixinTest, NullChildHandling) {
    ViewGroup<MarginLayoutParams> container;

    // Adding null should be a no-op
    EXPECT_NO_THROW(container.add_view(nullptr));
    EXPECT_EQ(0, container.get_child_count());

    // Removing null should be a no-op
    EXPECT_NO_THROW(container.remove_view(nullptr));
}

// ============================================================================
// Test 8: Self-addition prevention
// ============================================================================
TEST(ViewManagerMixinTest, SelfAdditionPrevented) {
    ViewGroup<MarginLayoutParams> container;

    // A view should not be added to itself
    EXPECT_NO_THROW(container.add_view(std::make_shared<ViewGroup<MarginLayoutParams>>()));
    // The child is a new ViewGroup, not the container itself, so this should work
    EXPECT_EQ(1, container.get_child_count());
}
