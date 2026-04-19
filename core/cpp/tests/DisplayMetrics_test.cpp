#include <gtest/gtest.h>
#include <android/util/DisplayMetrics.h>

using namespace android::util;

TEST(DisplayMetricsTest, Defaults) {
    DisplayMetrics dm;
    dm.set_to_defaults();
    
    EXPECT_EQ(dm.density_dpi, DisplayMetrics::DENSITY_MEDIUM);
    EXPECT_FLOAT_EQ(dm.density, 1.0f);
}

TEST(DisplayMetricsTest, XHighDensity) {
    DisplayMetrics dm;
    dm.density_dpi = DisplayMetrics::DENSITY_XHIGH;
    dm.density = static_cast<float>(dm.density_dpi) / static_cast<float>(DisplayMetrics::DENSITY_MEDIUM);
    
    EXPECT_FLOAT_EQ(dm.density, 2.0f);
}

TEST(DisplayMetricsTest, UnitConversionSimulation) {
    DisplayMetrics dm;
    dm.density = 2.0f; // xhdpi
    
    float dp = 16.0f;
    float px = dp * dm.density;
    
    EXPECT_FLOAT_EQ(px, 32.0f);
}
