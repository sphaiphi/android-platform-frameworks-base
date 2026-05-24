#include <gtest/gtest.h>
#include <android/view/DisplayInfo.h>

TEST(DisplayInfoTest, PropertyManagement) {
    using namespace android::view;
    
    DisplayInfo info;
    info.logicalWidth = 1080;
    info.logicalHeight = 1920;
    info.rotation = 0;
    
    EXPECT_EQ(1080, info.logicalWidth);
    EXPECT_EQ(1920, info.logicalHeight);
    EXPECT_EQ(0, info.rotation);
}
