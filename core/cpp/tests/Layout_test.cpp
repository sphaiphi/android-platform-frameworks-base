#include <gtest/gtest.h>
#include <android/view/ViewGroup.h>
#include <android/view/View.h>
#include <memory>
#include <algorithm>

using namespace android::view;

class VerticalLayout : public ViewGroup {
public:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override {
        int32_t total_height = 0;
        int32_t max_width = 0;
        
        for (int i = 0; i < get_child_count(); ++i) {
            auto child = get_child_at(i);
            if (child->get_measured_width() == 0 && child->get_measured_height() == 0) {
                child->measure(width_measure_spec, View::MeasureSpec::make_measure_spec(0, View::MeasureSpec::UNSPECIFIED));
            }
            total_height += child->get_measured_height();
            max_width = std::max(max_width, child->get_measured_width());
        }
        
        set_measured_dimension(max_width, total_height);
    }
    
    void on_layout(bool /*changed*/, int32_t /*left*/, int32_t /*top*/, int32_t /*right*/, int32_t /*bottom*/) override {
        int32_t current_top = 0;
        for (int i = 0; i < get_child_count(); ++i) {
            auto child = get_child_at(i);
            child->layout(0, current_top, child->get_measured_width(), current_top + child->get_measured_height());
            current_top += child->get_measured_height();
        }
    }
};

class LayoutTest : public ::testing::Test {
protected:
    std::shared_ptr<VerticalLayout> layout;
    
    void SetUp() override {
        layout = std::make_shared<VerticalLayout>();
    }
};

TEST_F(LayoutTest, VerticalStacking) {
    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();
    
    layout->add_view(child1);
    layout->add_view(child2);
    
    // Mocking child measurement behavior for this test
    // Usually children would override on_measure
    child1->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY), 
                   View::MeasureSpec::make_measure_spec(50, View::MeasureSpec::EXACTLY));
    child2->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY), 
                   View::MeasureSpec::make_measure_spec(70, View::MeasureSpec::EXACTLY));
    
    layout->measure(View::MeasureSpec::make_measure_spec(100, View::MeasureSpec::EXACTLY),
                   View::MeasureSpec::make_measure_spec(200, View::MeasureSpec::EXACTLY));
    
    EXPECT_EQ(100, layout->get_measured_width());
    EXPECT_EQ(120, layout->get_measured_height());
    
    layout->layout(0, 0, 100, 120);
    
    EXPECT_EQ(0, child1->get_top());
    EXPECT_EQ(50, child1->get_bottom());
    
    EXPECT_EQ(50, child2->get_top());
    EXPECT_EQ(120, child2->get_bottom());
}
