#include <gtest/gtest.h>
#include <android/widget/TextView.h>
#include <memory>

using namespace android::view;
using namespace android::widget;

TEST(TextViewTest, TextProperty) {
    auto textView = std::make_shared<TextView>();
    textView->set_text("Hello World");
    EXPECT_EQ("Hello World", textView->get_text());
}

TEST(TextViewTest, Measurement) {
    auto textView = std::make_shared<TextView>();
    textView->set_text("Hello");
    
    // In our simplified implementation, we'll assume each character is 10 units wide
    // and height is constant 20.
    textView->measure(View::MeasureSpec::make_measure_spec(0, View::MeasureSpec::UNSPECIFIED),
                      View::MeasureSpec::make_measure_spec(0, View::MeasureSpec::UNSPECIFIED));
    
    EXPECT_EQ(50, textView->get_measured_width());
    EXPECT_EQ(20, textView->get_measured_height());
}
