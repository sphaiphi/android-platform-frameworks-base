#include <gtest/gtest.h>
#include <android/content/res/Configuration.h>

using namespace android::content::res;

class ConfigurationCtsTest : public ::testing::Test {
};

TEST_F(ConfigurationCtsTest, TestConstructor) {
    Configuration config;
    EXPECT_EQ(Configuration::ORIENTATION_UNDEFINED, config.orientation);
}

TEST_F(ConfigurationCtsTest, TestDiff) {
    Configuration config1;
    config1.orientation = Configuration::ORIENTATION_LANDSCAPE;
    
    Configuration config2;
    config2.orientation = Configuration::ORIENTATION_PORTRAIT;
    
    uint32_t diff = config1.diff(config2);
    EXPECT_NE(0, diff & Configuration::CONFIG_ORIENTATION);
    
    config2.orientation = Configuration::ORIENTATION_LANDSCAPE;
    diff = config1.diff(config2);
    EXPECT_EQ(0, diff & Configuration::CONFIG_ORIENTATION);
}

TEST_F(ConfigurationCtsTest, TestUpdateFrom) {
    Configuration config1;
    config1.orientation = Configuration::ORIENTATION_LANDSCAPE;
    
    Configuration config2;
    config2.orientation = Configuration::ORIENTATION_PORTRAIT;
    
    uint32_t changed = config1.update_from(config2);
    EXPECT_NE(0, changed & Configuration::CONFIG_ORIENTATION);
    EXPECT_EQ(Configuration::ORIENTATION_PORTRAIT, config1.orientation);
}
