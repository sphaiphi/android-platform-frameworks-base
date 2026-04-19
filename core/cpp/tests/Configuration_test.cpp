#include <gtest/gtest.h>
#include <android/content/res/Configuration.h>

using namespace android::content::res;

TEST(ConfigurationTest, DiffOrientation) {
    Configuration c1;
    c1.orientation = Configuration::ORIENTATION_PORTRAIT;
    
    Configuration c2;
    c2.orientation = Configuration::ORIENTATION_LANDSCAPE;
    
    EXPECT_EQ(c1.diff(c2), Configuration::CONFIG_ORIENTATION);
}

TEST(ConfigurationTest, UpdateFrom) {
    Configuration c1;
    c1.set_to_defaults();
    
    Configuration c2;
    c2.orientation = Configuration::ORIENTATION_LANDSCAPE;
    c2.mcc = 310;
    
    uint32_t changes = c1.update_from(c2);
    
    EXPECT_EQ(changes, Configuration::CONFIG_ORIENTATION | Configuration::CONFIG_MCC);
    EXPECT_EQ(c1.orientation, Configuration::ORIENTATION_LANDSCAPE);
    EXPECT_EQ(c1.mcc, 310);
}

TEST(ConfigurationTest, Equality) {
    Configuration c1;
    c1.orientation = Configuration::ORIENTATION_PORTRAIT;
    
    Configuration c2;
    c2.orientation = Configuration::ORIENTATION_PORTRAIT;
    
    EXPECT_TRUE(c1 == c2);
    
    c2.orientation = Configuration::ORIENTATION_LANDSCAPE;
    EXPECT_FALSE(c1 == c2);
}
