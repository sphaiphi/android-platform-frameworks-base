#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewGroup.h>

TEST(ViewTest, VisibilityManagement) {
    using namespace android::view;
    View view;
    
    // Default visibility should be VISIBLE
    EXPECT_EQ(Visibility::Visible, view.get_visibility());

    view.set_visibility(Visibility::Invisible);
    EXPECT_EQ(Visibility::Invisible, view.get_visibility());

    view.set_visibility(Visibility::Gone);
    EXPECT_EQ(Visibility::Gone, view.get_visibility());

    view.set_visibility(Visibility::Visible);
    EXPECT_EQ(Visibility::Visible, view.get_visibility());
}

TEST(ViewTest, IdManagement) {
    using namespace android::view;
    View view;
    
    EXPECT_EQ(View::NO_ID, view.get_id());
    
    view.set_id(100);
    EXPECT_EQ(100, view.get_id());
}

TEST(ViewTest, EnabledState) {
    using namespace android::view;
    View view;
    
    EXPECT_TRUE(view.is_enabled());
    
    view.set_enabled(false);
    EXPECT_FALSE(view.is_enabled());
}

TEST(ViewTest, CoordinateSystem) {
    using namespace android::view;
    View view;
    
    // Initial coordinates should be zero
    EXPECT_EQ(0, view.get_left());
    EXPECT_EQ(0, view.get_top());
    EXPECT_EQ(0, view.get_right());
    EXPECT_EQ(0, view.get_bottom());
    EXPECT_EQ(0, view.get_width());
    EXPECT_EQ(0, view.get_height());

    view.layout(10, 20, 110, 120);
    EXPECT_EQ(10, view.get_left());
    EXPECT_EQ(20, view.get_top());
    EXPECT_EQ(110, view.get_right());
    EXPECT_EQ(120, view.get_bottom());
    EXPECT_EQ(100, view.get_width());
    EXPECT_EQ(100, view.get_height());
}

TEST(ViewTest, MeasurePass) {
    using namespace android::view;
    View view;
    
    // Initial measured dimensions should be zero
    EXPECT_EQ(0, view.get_measured_width());
    EXPECT_EQ(0, view.get_measured_height());

    // Simple measure call (specs simplified for now)
    view.measure(100, 200);
    EXPECT_EQ(100, view.get_measured_width());
    EXPECT_EQ(200, view.get_measured_height());
}

TEST(ViewTest, GetResources) {
    using namespace android::view;
    View view;
    // In our C++ implementation, we don't have a full Resources object yet,
    // but we can verify the architectural intent if/when it's added.
    // For now, this is a placeholder for CTS parity.
}

TEST(ViewTest, GetParent) {
    using namespace android::view;
    auto parent = std::make_shared<ViewGroup<MarginLayoutParams>>();
    auto child = std::make_shared<View>();
    
    EXPECT_EQ(nullptr, child->get_parent());
    parent->add_view(child);
    EXPECT_EQ(parent.get(), child->get_parent());
}

TEST(ViewTest, FindViewById) {
    using namespace android::view;
    ViewGroup<MarginLayoutParams> parent;
    auto child = std::make_shared<View>();
    child->set_id(100);
    parent.add_view(child);

    // In a real implementation, findViewById would traverse the hierarchy.
    // Our current ViewGroup doesn't implement it yet, so this serves as a
    // requirement for Phase 5 if needed, or we can implement a simple version.
}

// ============================================================================
// Animated property tests
// ============================================================================

TEST(ViewTest, AnimatedPropertyDefaults) {
    using namespace android::view;
    View view;

    // Default values match Java View
    EXPECT_FLOAT_EQ(0.0f, view.get_translation_x());
    EXPECT_FLOAT_EQ(0.0f, view.get_translation_y());
    EXPECT_FLOAT_EQ(1.0f, view.get_alpha());
    EXPECT_FLOAT_EQ(0.0f, view.get_rotation());
    EXPECT_FLOAT_EQ(1.0f, view.get_scale_x());
    EXPECT_FLOAT_EQ(1.0f, view.get_scale_y());
}

TEST(ViewTest, AnimatedPropertySetGet) {
    using namespace android::view;
    View view;

    view.set_translation_x(10.5f);
    EXPECT_FLOAT_EQ(10.5f, view.get_translation_x());

    view.set_alpha(0.75f);
    EXPECT_FLOAT_EQ(0.75f, view.get_alpha());

    view.set_rotation(45.0f);
    EXPECT_FLOAT_EQ(45.0f, view.get_rotation());

    view.set_scale_x(2.0f);
    EXPECT_FLOAT_EQ(2.0f, view.get_scale_x());

    view.set_scale_y(0.5f);
    EXPECT_FLOAT_EQ(0.5f, view.get_scale_y());
}

TEST(ViewTest, ComputedPositionIncludesTranslation) {
    using namespace android::view;
    View view;

    // Layout at origin
    view.layout(100, 200, 200, 300);

    // Without translation, x/y = left/top
    EXPECT_FLOAT_EQ(100.0f, view.get_x());
    EXPECT_FLOAT_EQ(200.0f, view.get_y());

    // With translation
    view.set_translation_x(50.0f);
    view.set_translation_y(25.0f);

    // x = left + translationX, y = top + translationY
    EXPECT_FLOAT_EQ(150.0f, view.get_x());
    EXPECT_FLOAT_EQ(225.0f, view.get_y());
}

TEST(ViewTest, InvalidateMethodExists) {
    using namespace android::view;
    View view;

    // invalidate() should not throw
    EXPECT_NO_THROW(view.invalidate());
}

TEST(ViewTest, AnimateMethodReturnsSharedPtr) {
    using namespace android::view;
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);

    auto vpa = view->animate();
    // animate() returns a shared_ptr to ViewPropertyAnimator
    // The method should not throw
    EXPECT_NE(vpa, nullptr);
}
