#include <gtest/gtest.h>
#include <android/widget/RelativeLayout.h>
#include <android/view/View.h>
#include <memory>

using namespace android::view;
using namespace android::widget;

TEST(RelativeLayoutTest, ParentAlignment) {
    auto layout = std::make_shared<RelativeLayout>();
    
    auto child = std::make_shared<View>();
    auto lp = std::make_shared<RelativeLayout::LayoutParams>(50, 50);
    lp->add_rule(RelativeLayout::ALIGN_PARENT_RIGHT);
    lp->add_rule(RelativeLayout::ALIGN_PARENT_BOTTOM);
    child->set_layout_params(lp);
    layout->add_view(child);
    
    layout->measure(View::MeasureSpec::make(100, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make(100, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 100, 100);
    
    EXPECT_EQ(50, child->get_left());
    EXPECT_EQ(50, child->get_top());
    EXPECT_EQ(100, child->get_right());
    EXPECT_EQ(100, child->get_bottom());
}

TEST(RelativeLayoutTest, SiblingAlignment) {
    auto layout = std::make_shared<RelativeLayout>();
    
    auto child1 = std::make_shared<View>();
    child1->set_id(1);
    child1->set_layout_params(std::make_shared<RelativeLayout::LayoutParams>(50, 50));
    layout->add_view(child1);
    
    auto child2 = std::make_shared<View>();
    child2->set_id(2);
    auto lp2 = std::make_shared<RelativeLayout::LayoutParams>(50, 50);
    lp2->add_rule(RelativeLayout::BELOW, 1);
    lp2->add_rule(RelativeLayout::RIGHT_OF, 1);
    child2->set_layout_params(lp2);
    layout->add_view(child2);
    
    layout->measure(View::MeasureSpec::make(200, View::MeasureSpec::AT_MOST),
                    View::MeasureSpec::make(200, View::MeasureSpec::AT_MOST));
    
    layout->layout(0, 0, 200, 200);
    
    // child1 at (0,0)
    EXPECT_EQ(0, child1->get_left());
    EXPECT_EQ(0, child1->get_top());
    
    // child2 should be to the right and below child1
    EXPECT_EQ(50, child2->get_left());
    EXPECT_EQ(50, child2->get_top());
}
