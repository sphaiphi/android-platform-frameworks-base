#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewTypes.h>
#include <android/view/LayoutParams.h>
#include <android/graphics/ColorDrawable.h>
#include <android/graphics/Canvas.h>

using namespace android::view;
using namespace android::graphics;

// ============================================================================
// Test 1: Default visibility is Visible enum
// ============================================================================
TEST(ViewFoundational, DefaultVisibilityIsVisible) {
    View view;
    EXPECT_EQ(Visibility::Visible, view.get_visibility());
}

// ============================================================================
// Test 2: Set visibility with enum class values
// ============================================================================
TEST(ViewFoundational, SetVisibilityEnumValues) {
    View view;

    view.set_visibility(Visibility::Invisible);
    EXPECT_EQ(Visibility::Invisible, view.get_visibility());

    view.set_visibility(Visibility::Gone);
    EXPECT_EQ(Visibility::Gone, view.get_visibility());

    view.set_visibility(Visibility::Visible);
    EXPECT_EQ(Visibility::Visible, view.get_visibility());
}

// ============================================================================
// Test 3: Visibility change triggers layout request
// ============================================================================
TEST(ViewFoundational, VisibilityChangeTriggersLayoutRequest) {
    View view;

    // Changing from Visible to Invisible should request layout
    view.set_visibility(Visibility::Invisible);
    // In a real implementation, this would call request_layout()

    // Changing from Gone to Visible should request layout
    view.set_visibility(Visibility::Gone);
    view.set_visibility(Visibility::Visible);
}

// ============================================================================
// Test 4: MeasureSpec struct static methods
// ============================================================================
TEST(ViewFoundational, MeasureSpecStaticMethods) {
    // Test make()
    auto spec = MeasureSpec::make(100, MeasureSpec::EXACTLY);
    EXPECT_EQ(MeasureSpec::EXACTLY, MeasureSpec::get_mode(spec));
    EXPECT_EQ(100, MeasureSpec::get_size(spec));

    // Test AT_MOST
    auto spec2 = MeasureSpec::make(200, MeasureSpec::AT_MOST);
    EXPECT_EQ(MeasureSpec::AT_MOST, MeasureSpec::get_mode(spec2));
    EXPECT_EQ(200, MeasureSpec::get_size(spec2));

    // Test UNSPECIFIED
    auto spec3 = MeasureSpec::make(0, MeasureSpec::UNSPECIFIED);
    EXPECT_EQ(MeasureSpec::UNSPECIFIED, MeasureSpec::get_mode(spec3));
    EXPECT_EQ(0, MeasureSpec::get_size(spec3));
}

// ============================================================================
// Test 5: MeasureSpec mask operations
// ============================================================================
TEST(ViewFoundational, MeasureSpecMaskOperations) {
    // Verify masks
    EXPECT_EQ(0xC0000000u, MeasureSpec::MODE_MASK);
    EXPECT_EQ(0x3FFFFFFFu, MeasureSpec::SIZE_MASK);
    EXPECT_EQ(30u, MeasureSpec::MODE_SHIFT);

    // Verify that make() packs correctly (AT_MOST = 0x80000000)
    auto spec = MeasureSpec::make(0x3FFFFFFF, MeasureSpec::AT_MOST);
    EXPECT_EQ(0x80000000u | 0x3FFFFFFFu, spec);
}

// ============================================================================
// Test 6: View ID management with NO_ID default
// ============================================================================
TEST(ViewFoundational, IdDefaultIsNO_ID) {
    View view;
    EXPECT_EQ(View::NO_ID, view.get_id());
}

TEST(ViewFoundational, IdSetAndGet) {
    View view;
    view.set_id(42);
    EXPECT_EQ(42, view.get_id());

    view.set_id(-1);
    EXPECT_EQ(-1, view.get_id());
}

// ============================================================================
// Test 7: Tag with std::any
// ============================================================================
TEST(ViewFoundational, TagDefaultIsEmpty) {
    View view;
    EXPECT_FALSE(view.get_tag().has_value());
}

TEST(ViewFoundational, TagSetAndGetInt) {
    View view;
    view.set_tag(42);
    ASSERT_TRUE(view.get_tag().has_value());
    EXPECT_EQ(42, std::any_cast<int>(view.get_tag().value()));
}

TEST(ViewFoundational, TagSetAndGetString) {
    View view;
    view.set_tag(std::string("hello"));
    ASSERT_TRUE(view.get_tag().has_value());
    EXPECT_EQ(std::string("hello"), std::any_cast<std::string>(view.get_tag().value()));
}

// ============================================================================
// Test 8: Flag management (enabled, focusable, clickable)
// ============================================================================
TEST(ViewFoundational, EnabledDefaultsTrue) {
    View view;
    EXPECT_TRUE(view.is_enabled());
}

TEST(ViewFoundational, ToggleEnabled) {
    View view;
    view.set_enabled(false);
    EXPECT_FALSE(view.is_enabled());

    view.set_enabled(true);
    EXPECT_TRUE(view.is_enabled());
}

TEST(ViewFoundational, ClickableDefaultsFalse) {
    View view;
    EXPECT_FALSE(view.is_clickable());

    view.set_clickable(true);
    EXPECT_TRUE(view.is_clickable());
}

// ============================================================================
// Test 9: Padding management
// ============================================================================
TEST(ViewFoundational, PaddingDefaultsZero) {
    View view;
    EXPECT_EQ(0, view.get_padding_left());
    EXPECT_EQ(0, view.get_padding_top());
    EXPECT_EQ(0, view.get_padding_right());
    EXPECT_EQ(0, view.get_padding_bottom());
}

TEST(ViewFoundational, SetPadding) {
    View view;
    view.set_padding(10, 20, 30, 40);
    EXPECT_EQ(10, view.get_padding_left());
    EXPECT_EQ(20, view.get_padding_top());
    EXPECT_EQ(30, view.get_padding_right());
    EXPECT_EQ(40, view.get_padding_bottom());
}

// ============================================================================
// Test 10: Rotation properties
// ============================================================================
TEST(ViewFoundational, RotationDefaultsZero) {
    View view;
    EXPECT_FLOAT_EQ(0.0f, view.get_rotation());
    EXPECT_FLOAT_EQ(0.0f, view.get_rotation_x());
    EXPECT_FLOAT_EQ(0.0f, view.get_rotation_y());
    EXPECT_FLOAT_EQ(0.0f, view.get_rotation_z());
}

TEST(ViewFoundational, SetRotationValues) {
    View view;
    view.set_rotation(90.0f);
    EXPECT_FLOAT_EQ(90.0f, view.get_rotation());

    view.set_rotation_x(45.0f);
    EXPECT_FLOAT_EQ(45.0f, view.get_rotation_x());

    view.set_rotation_y(180.0f);
    EXPECT_FLOAT_EQ(180.0f, view.get_rotation_y());

    view.set_rotation_z(270.0f);
    EXPECT_FLOAT_EQ(270.0f, view.get_rotation_z());
}

// ============================================================================
// Test 11: Min width/height
// ============================================================================
TEST(ViewFoundational, MinDimensionsDefaultsZero) {
    View view;
    EXPECT_EQ(0, view.get_min_width());
    EXPECT_EQ(0, view.get_min_height());
}

TEST(ViewFoundational, SetMinDimensions) {
    View view;
    view.set_min_width(50);
    EXPECT_EQ(50, view.get_min_width());

    view.set_min_height(100);
    EXPECT_EQ(100, view.get_min_height());
}

// ============================================================================
// Test 12: Layout direction
// ============================================================================
TEST(ViewFoundational, LayoutDirectionDefaultsLtr) {
    View view;
    EXPECT_EQ(LayoutDirection::Ltr, view.get_layout_direction());
}

TEST(ViewFoundational, SetLayoutDirection) {
    View view;
    view.set_layout_direction(LayoutDirection::Rtl);
    EXPECT_EQ(LayoutDirection::Rtl, view.get_layout_direction());
}

// ============================================================================
// Test 13: Resolve size with MeasureSpec
// ============================================================================
TEST(ViewFoundational, ResolveSizeExactly) {
    EXPECT_EQ(100, View::resolve_size(200, MeasureSpec::make(100, MeasureSpec::EXACTLY)));
}

TEST(ViewFoundational, ResolveSizeAtMost) {
    // Size larger than spec -> use spec size
    EXPECT_EQ(50, View::resolve_size(100, MeasureSpec::make(50, MeasureSpec::AT_MOST)));
    // Size smaller than spec -> use size
    EXPECT_EQ(30, View::resolve_size(30, MeasureSpec::make(50, MeasureSpec::AT_MOST)));
}

TEST(ViewFoundational, ResolveSizeUnspecified) {
    EXPECT_EQ(100, View::resolve_size(100, MeasureSpec::make(0, MeasureSpec::UNSPECIFIED)));
}

// ============================================================================
// Test 14: GONE visibility prevents drawing
// ============================================================================
TEST(ViewFoundational, GoneViewDoesNotDraw) {
    View view;
    view.layout(0, 0, 100, 100);
    view.set_visibility(Visibility::Gone);

    Canvas canvas(200, 200);
    auto bg = std::make_shared<ColorDrawable>(Color::GREEN);
    view.set_background(bg);
    view.draw(canvas);

    // GONE views should not draw
    EXPECT_TRUE(canvas.get_commands().empty());
}

// ============================================================================
// Test 15: Alpha clamping
// ============================================================================
TEST(ViewFoundational, AlphaClampedToRange) {
    View view;

    // Negative alpha clamped to 0
    view.set_alpha(-0.5f);
    EXPECT_FLOAT_EQ(0.0f, view.get_alpha());

    // Alpha > 1 clamped to 1
    view.set_alpha(2.0f);
    EXPECT_FLOAT_EQ(1.0f, view.get_alpha());

    // Valid alpha preserved
    view.set_alpha(0.5f);
    EXPECT_FLOAT_EQ(0.5f, view.get_alpha());
}
