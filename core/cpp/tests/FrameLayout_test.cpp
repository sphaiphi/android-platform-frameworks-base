#include <gtest/gtest.h>
#include <android/widget/FrameLayout.h>
#include <android/view/View.h>
#include <android/view/Gravity.h>
#include <memory>

using namespace android::view;
using namespace android::widget;

TEST(FrameLayoutTest, ZAxisLayering) {
    auto layout = std::make_shared<FrameLayout>();
    
    auto child1 = std::make_shared<View>();
    child1->set_layout_params(std::make_shared<ViewGroup::LayoutParams>(100, 100));
    layout->add_view(child1);
    
    auto child2 = std::make_shared<View>();
    child2->set_layout_params(std::make_shared<ViewGroup::LayoutParams>(50, 50));
    layout->add_view(child2);
    
    layout->measure(View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::AT_MOST),
                    View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::AT_MOST));
    
    EXPECT_EQ(100, layout->get_measured_width());
    EXPECT_EQ(100, layout->get_measured_height());
    
    layout->layout(0, 0, 100, 100);
    
    // Both should be at (0,0) by default
    EXPECT_EQ(0, child1->get_left());
    EXPECT_EQ(0, child1->get_top());
    
    EXPECT_EQ(0, child2->get_left());
    EXPECT_EQ(0, child2->get_top());
}

TEST(FrameLayoutTest, GravityPositioning) {
    auto layout = std::make_shared<FrameLayout>();
    
    auto child = std::make_shared<View>();
    auto lp = std::make_shared<FrameLayout::LayoutParams>(50, 50);
    lp->gravity = Gravity::RIGHT | Gravity::BOTTOM;
    child->set_layout_params(lp);
    layout->add_view(child);
    
    layout->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 100, 100);
    
    EXPECT_EQ(50, child->get_left());
    EXPECT_EQ(50, child->get_top());
    EXPECT_EQ(100, child->get_right());
    EXPECT_EQ(100, child->get_bottom());
}
