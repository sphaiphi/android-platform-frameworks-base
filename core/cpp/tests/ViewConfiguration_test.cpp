#include <gtest/gtest.h>
#include <android/view/ViewConfiguration.h>

TEST(ViewConfigurationTest, DefaultValues) {
    using namespace android::view;
    
    // Test static constants
    EXPECT_EQ(4, ViewConfiguration::get_scroll_bar_size());
    EXPECT_EQ(64, ViewConfiguration::get_pressed_state_duration());
    EXPECT_EQ(400, ViewConfiguration::get_long_press_timeout());
}
