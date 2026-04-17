#include <gtest/gtest.h>
#include <android/widget/LinearLayout.h>
#include <android/widget/FrameLayout.h>
#include <android/view/View.h>
#include <android/view/Gravity.h>
#include <memory>

using namespace android::view;
using namespace android::widget;

TEST(LinearLayoutGravityTest, VerticalBlockCentering) {
    auto layout = std::make_shared<LinearLayout>();
    layout->set_orientation(LinearLayout::VERTICAL);
    layout->set_gravity(Gravity::CENTER_VERTICAL);
    
    auto child = std::make_shared<View>();
    child->set_layout_params(std::make_shared<LinearLayout::LayoutParams>(100, 50));
    layout->add_view(child);
    
    layout->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 100, 200);
    
    // If centered vertically, child should be at (0, 75, 100, 125)
    EXPECT_EQ(75, child->get_top());
    EXPECT_EQ(125, child->get_bottom());
}

TEST(LinearLayoutGravityTest, HorizontalBlockCentering) {
    auto layout = std::make_shared<LinearLayout>();
    layout->set_orientation(LinearLayout::HORIZONTAL);
    layout->set_gravity(Gravity::CENTER_HORIZONTAL);
    
    auto child = std::make_shared<View>();
    child->set_layout_params(std::make_shared<LinearLayout::LayoutParams>(50, 100));
    layout->add_view(child);
    
    layout->measure(View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 200, 100);
    
    // If centered horizontally, child should be at (75, 0, 125, 100)
    EXPECT_EQ(75, child->get_left());
    EXPECT_EQ(125, child->get_right());
}

TEST(LinearLayoutGravityTest, MixedGravity) {
    auto layout = std::make_shared<LinearLayout>();
    layout->set_orientation(LinearLayout::VERTICAL);
    layout->set_gravity(Gravity::CENTER_VERTICAL | Gravity::CENTER_HORIZONTAL);
    
    auto child = std::make_shared<View>();
    child->set_layout_params(std::make_shared<LinearLayout::LayoutParams>(50, 50));
    layout->add_view(child);
    
    layout->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 100, 100);
    
    // Should be at (25, 25, 75, 75)
    EXPECT_EQ(25, child->get_left());
    EXPECT_EQ(25, child->get_top());
}

TEST(FrameLayoutGravityTest, CenterAlignment) {
    auto layout = std::make_shared<FrameLayout>();
    
    auto child = std::make_shared<View>();
    auto lp = std::make_shared<FrameLayout::LayoutParams>(40, 40);
    lp->gravity = Gravity::CENTER;
    child->set_layout_params(lp);
    layout->add_view(child);
    
    layout->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 100, 100);
    
    // Should be at (30, 30, 70, 70)
    EXPECT_EQ(30, child->get_left());
    EXPECT_EQ(30, child->get_top());
}

TEST(FrameLayoutGravityTest, MixedAlignment) {
    auto layout = std::make_shared<FrameLayout>();
    
    auto child1 = std::make_shared<View>();
    auto lp1 = std::make_shared<FrameLayout::LayoutParams>(20, 20, Gravity::TOP | Gravity::RIGHT);
    child1->set_layout_params(lp1);
    layout->add_view(child1);
    
    auto child2 = std::make_shared<View>();
    auto lp2 = std::make_shared<FrameLayout::LayoutParams>(20, 20, Gravity::BOTTOM | Gravity::LEFT);
    child2->set_layout_params(lp2);
    layout->add_view(child2);
    
    layout->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY));
    
    layout->layout(0, 0, 100, 100);
    
    EXPECT_EQ(80, child1->get_left());
    EXPECT_EQ(0, child1->get_top());
    
    EXPECT_EQ(0, child2->get_left());
    EXPECT_EQ(80, child2->get_top());
}
