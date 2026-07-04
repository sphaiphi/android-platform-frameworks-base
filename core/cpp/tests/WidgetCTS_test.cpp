#include <gtest/gtest.h>
#include <android/widget/LinearLayout.h>
#include <android/widget/FrameLayout.h>
#include <android/widget/RelativeLayout.h>
#include <android/widget/TextView.h>
#include <android/widget/Button.h>
#include <android/view/View.h>
#include <android/view/Gravity.h>
#include <memory>
#include <string>

namespace android::view {

class WidgetCTSMockView : public View {
public:
    void set_measured_dimension_public(int32_t width, int32_t height) {
        set_measured_dimension(width, height);
    }

protected:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override {
        // Do nothing, keep manual dimensions
    }
};

} // namespace android::view

using namespace android::view;
using namespace android::widget;

class WidgetCTSTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class MockButton : public Button {
public:
    bool perform_click() {
        // Since Button's on_touch_event calls the listener on ACTION_UP,
        // we can simulate that.
        MotionEvent down(MotionEvent::ACTION_DOWN, 0, 0);
        on_touch_event(down);
        MotionEvent up(MotionEvent::ACTION_UP, 0, 0);
        return on_touch_event(up);
    }
};

/**
 * Ported from LinearLayoutTest.java: testWeightDistribution
 */
TEST_F(WidgetCTSTest, LinearLayout_WeightDistribution) {
    auto parent = std::make_shared<LinearLayout>();
    int size = 100;
    int spec = View::MeasureSpec::make(size, View::MeasureSpec::EXACTLY);

    for (int i = 0; i < 3; i++) {
        auto child = std::make_shared<View>();
        auto lp = std::make_shared<LinearLayout::LayoutParams>(0, 0, 1.0f);
        lp->width = LinearLayout::LayoutParams::MATCH_PARENT;
        child->set_layout_params(lp);
        parent->add_view(child);
    }

    parent->set_orientation(LinearLayout::VERTICAL);
    parent->measure(spec, spec);
    parent->layout(0, 0, size, size);

    EXPECT_EQ(100, parent->get_width());
    EXPECT_EQ(100, parent->get_child_at(0)->get_width());
    EXPECT_EQ(100, parent->get_child_at(1)->get_width());
    EXPECT_EQ(100, parent->get_child_at(2)->get_width());
    
    EXPECT_EQ(100, parent->get_height());
    // 100 / 3 = 33.33... Android CTS expects 33, 33, 34
    EXPECT_EQ(33, parent->get_child_at(0)->get_height());
    EXPECT_EQ(33, parent->get_child_at(1)->get_height());
    EXPECT_EQ(34, parent->get_child_at(2)->get_height());
}

/**
 * Ported from FrameLayoutTest.java: testAccessMeasureAllChildren
 * (Simplified for current implementation)
 */
TEST_F(WidgetCTSTest, FrameLayout_VisibilityAffectsMeasurement) {
    auto frameLayout = std::make_shared<FrameLayout>();
    
    auto child1 = std::make_shared<WidgetCTSMockView>();
    child1->set_measured_dimension_public(60, 30);
    frameLayout->add_view(child1);

    auto child2 = std::make_shared<WidgetCTSMockView>();
    child2->set_measured_dimension_public(50, 15);
    frameLayout->add_view(child2);

    // Initial measure with both visible
    frameLayout->measure(View::MeasureSpec::make(100, View::MeasureSpec::AT_MOST),
                        View::MeasureSpec::make(100, View::MeasureSpec::AT_MOST));
    
    EXPECT_EQ(60, frameLayout->get_measured_width());
    EXPECT_EQ(30, frameLayout->get_measured_height());

    // child1 GONE, should measure based on child2
    child1->set_visibility(Visibility::Gone);
    frameLayout->measure(View::MeasureSpec::make(100, View::MeasureSpec::AT_MOST),
                        View::MeasureSpec::make(100, View::MeasureSpec::AT_MOST));
    
    EXPECT_EQ(50, frameLayout->get_measured_width());
    EXPECT_EQ(15, frameLayout->get_measured_height());
}

/**
 * Ported from RelativeLayoutTest.java: testAccessGravity (Parent alignment)
 */
TEST_F(WidgetCTSTest, RelativeLayout_ParentAlignment) {
    auto relativeLayout = std::make_shared<RelativeLayout>();
    
    auto child = std::make_shared<View>();
    auto lp = std::make_shared<RelativeLayout::LayoutParams>(20, 20);
    lp->add_rule(RelativeLayout::ALIGN_PARENT_RIGHT);
    lp->add_rule(RelativeLayout::ALIGN_PARENT_BOTTOM);
    child->set_layout_params(lp);
    relativeLayout->add_view(child);

    relativeLayout->measure(View::MeasureSpec::make(100, View::MeasureSpec::EXACTLY),
                           View::MeasureSpec::make(100, View::MeasureSpec::EXACTLY));
    relativeLayout->layout(0, 0, 100, 100);

    EXPECT_EQ(80, child->get_left());
    EXPECT_EQ(80, child->get_top());
    EXPECT_EQ(100, child->get_right());
    EXPECT_EQ(100, child->get_bottom());
}

/**
 * Ported from TextViewTest.java: testAccessText
 */
TEST_F(WidgetCTSTest, TextView_AccessText) {
    auto tv = std::make_shared<TextView>();
    std::string expected = "Hello World";
    tv->set_text(expected);
    EXPECT_EQ(expected, tv->get_text());

    tv->set_text("");
    EXPECT_EQ("", tv->get_text());
}

/**
 * Ported from ViewTest.java: testPerformClick (via Button)
 */
TEST_F(WidgetCTSTest, Button_PerformClick) {
    auto button = std::make_shared<MockButton>();
    bool clicked = false;
    
    button->set_on_click_listener([&clicked](View* v) {
        clicked = true;
    });

    EXPECT_FALSE(clicked);
    EXPECT_TRUE(button->perform_click());
    EXPECT_TRUE(clicked);
}
