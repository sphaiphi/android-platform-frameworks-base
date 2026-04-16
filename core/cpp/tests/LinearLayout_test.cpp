#include <gtest/gtest.h>
#include <android/widget/LinearLayout.h>
#include <android/view/View.h>
#include <memory>

using namespace android::view;
using namespace android::widget;

TEST(LinearLayoutTest, VerticalStacking) {
    auto layout = std::make_shared<LinearLayout>();
    layout->set_orientation(LinearLayout::VERTICAL);
    
    auto child1 = std::make_shared<View>();
    child1->set_layout_params(std::make_shared<ViewGroup::LayoutParams>(100, 50));
    layout->add_view(child1);
    
    auto child2 = std::make_shared<View>();
    child2->set_layout_params(std::make_shared<ViewGroup::LayoutParams>(100, 50));
    layout->add_view(child2);
    
    layout->measure(View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::EXACTLY),
                    View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::AT_MOST));
    
    EXPECT_EQ(100, layout->get_measured_width());
    EXPECT_EQ(100, layout->get_measured_height()); // 50 + 50
    
    layout->layout(0, 0, 100, 100);
    
    EXPECT_EQ(0, child1->get_top());
    EXPECT_EQ(50, child1->get_bottom());
    
    EXPECT_EQ(50, child2->get_top());
    EXPECT_EQ(100, child2->get_bottom());
}

TEST(LinearLayoutTest, HorizontalStacking) {
    auto layout = std::make_shared<LinearLayout>();
    layout->set_orientation(LinearLayout::HORIZONTAL);
    
    auto child1 = std::make_shared<View>();
    child1->set_layout_params(std::make_shared<ViewGroup::LayoutParams>(50, 100));
    layout->add_view(child1);
    
    auto child2 = std::make_shared<View>();
    child2->set_layout_params(std::make_shared<ViewGroup::LayoutParams>(50, 100));
    layout->add_view(child2);
    
    layout->measure(View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::AT_MOST),
                    View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::EXACTLY));
    
    EXPECT_EQ(100, layout->get_measured_width()); // 50 + 50
    EXPECT_EQ(100, layout->get_measured_height());
    
    layout->layout(0, 0, 100, 100);
    
    EXPECT_EQ(0, child1->get_left());
    EXPECT_EQ(50, child1->get_right());
    
    EXPECT_EQ(50, child2->get_left());
    EXPECT_EQ(100, child2->get_right());
}
