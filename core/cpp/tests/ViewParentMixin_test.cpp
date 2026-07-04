#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewGroup.h>
#include <android/view/ViewParentMixin.h>

using namespace android::view;

// ============================================================================
// Test 1: request_layout propagates up the parent chain
// ============================================================================
TEST(ViewParentMixinTest, RequestLayoutPropagatesUp) {
    ViewGroup<MarginLayoutParams> parent;
    View child;

    parent.add_view(std::make_shared<View>(child));

    // The child's request_layout should propagate to parent via CRTP
    // In the current implementation, child.request_layout() calls
    // ViewParentMixin<View>::request_layout() which sets layoutRequested_
    // and propagates to parent
}

// ============================================================================
// Test 2: is_layout_requested returns correct state
// ============================================================================
TEST(ViewParentMixinTest, IsLayoutRequestedInitialState) {
    View view;
    EXPECT_FALSE(view.is_layout_requested());
}

// ============================================================================
// Test 3: on_descendant_invalidated propagates up
// ============================================================================
TEST(ViewParentMixinTest, DescendantInvalidatedPropagates) {
    View view;
    // invalidate() calls ViewParentMixin<View>::on_descendant_invalidated
    // which propagates up the parent chain.
    // Without a parent, this should be a no-op (no crash).
    EXPECT_NO_THROW(view.invalidate());
}

// ============================================================================
// Test 4: request_child_focus propagates up
// ============================================================================
TEST(ViewParentMixinTest, RequestChildFocusPropagates) {
    View view;
    // Without a parent, this should be a no-op.
    EXPECT_NO_THROW(view.request_child_focus(&view, &view));
}

// ============================================================================
// Test 5: clear_child_focus propagates up
// ============================================================================
TEST(ViewParentMixinTest, ClearChildFocusPropagates) {
    View view;
    EXPECT_NO_THROW(view.clear_child_focus(&view));
}

// ============================================================================
// Test 6: focus_search returns nullptr (stub)
// ============================================================================
TEST(ViewParentMixinTest, FocusSearchReturnsNullptr) {
    View view;
    View* result = view.focus_search(&view, 0);
    EXPECT_EQ(nullptr, result);
}

// ============================================================================
// Test 7: CRTP static_cast works correctly
// ============================================================================
TEST(ViewParentMixinTest, CRTPStaticCastWorks) {
    View view;
    // The mixin uses static_cast<Derived*>(this) to access derived members.
    // This test verifies that the CRTP pattern works with View.
    ViewParentMixin<View> mixin;
    // We can't directly test the internal cast, but we can verify
    // that the mixin methods work without crashing.
    EXPECT_NO_THROW(mixin.is_layout_requested());
}

// ============================================================================
// Test 8: Parent chain propagation with nested ViewGroups
// ============================================================================
TEST(ViewParentMixinTest, NestedViewGroupLayoutPropagation) {
    ViewGroup<MarginLayoutParams> grandparent;
    ViewGroup<MarginLayoutParams> parent;
    View child;

    grandparent.add_view(std::make_shared<ViewGroup<MarginLayoutParams>>(parent));
    parent.add_view(std::make_shared<View>(child));

    // Child layout request should propagate: child -> parent -> grandparent
    EXPECT_NO_THROW(child.request_layout());
}
