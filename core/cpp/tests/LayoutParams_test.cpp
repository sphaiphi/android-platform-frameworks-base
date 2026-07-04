#include <gtest/gtest.h>
#include <android/view/ViewGroup.h>

using namespace android::view;

TEST(LayoutParamsTest, BasicMargins) {
    MarginLayoutParams lp(100, 200);
    
    EXPECT_EQ(100, lp.width);
    EXPECT_EQ(200, lp.height);
    
    lp.set_margins(10, 20, 30, 40);
    
    EXPECT_EQ(10, lp.left_margin);
    EXPECT_EQ(20, lp.top_margin);
    EXPECT_EQ(30, lp.right_margin);
    EXPECT_EQ(40, lp.bottom_margin);
}

TEST(LayoutParamsTest, MatchParentWrapContent) {
    EXPECT_EQ(-1, LayoutParams::MATCH_PARENT);
    EXPECT_EQ(-2, LayoutParams::WRAP_CONTENT);
}
