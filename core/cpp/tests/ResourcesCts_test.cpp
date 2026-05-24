#include <gtest/gtest.h>
#include <android/content/res/Resources.h>
#include <android/util/TypedValue.h>
#include <android/util/DisplayMetrics.h>
#include <memory>

using namespace android::content::res;
using namespace android::util;

class ResourcesCtsTest : public ::testing::Test {
protected:
    std::shared_ptr<AssetManager> assets;
    std::shared_ptr<DisplayMetrics> metrics;
    std::shared_ptr<Configuration> config;
    std::unique_ptr<Resources> resources;

    void SetUp() override {
        assets = std::make_shared<AssetManager>();
        metrics = std::make_shared<DisplayMetrics>();
        config = std::make_shared<Configuration>();
        
        // Initial setup: xhdpi (320dpi)
        metrics->density = 2.0f;
        metrics->density_dpi = 320;
        metrics->scaled_density = 2.0f;
        
        resources = std::make_unique<Resources>(assets, metrics, config);
    }

    void add_dimen(int32_t id, float value, int32_t unit) {
        TypedValue tv;
        tv.type = TypedValue::TYPE_DIMENSION;
        // Simple conversion for testing: assuming value is small integer for now
        // To be more precise, we should use a helper that encodes float into complex
        int32_t mantissa = static_cast<int32_t>(value);
        tv.data = (mantissa << TypedValue::COMPLEX_MANTISSA_SHIFT) | (unit << TypedValue::COMPLEX_UNIT_SHIFT);
        resources->add_resource(id, tv);
    }
};

TEST_F(ResourcesCtsTest, TestDimensionResolution) {
    int32_t res_id = 0x7f040001;
    
    // 16dp -> should be 32px on 2.0 density
    add_dimen(res_id, 16.0f, TypedValue::COMPLEX_UNIT_DP);
    
    auto result = resources->get_dimension(res_id);
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(32.0f, result.value());
    
    // Change density to mdpi (1.0)
    metrics->density = 1.0f;
    metrics->density_dpi = 160;
    resources->update_configuration(*config, *metrics);
    
    result = resources->get_dimension(res_id);
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(16.0f, result.value());
    
    // Change density to ldpi (0.75)
    metrics->density = 0.75f;
    metrics->density_dpi = 120;
    resources->update_configuration(*config, *metrics);
    
    result = resources->get_dimension(res_id);
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(12.0f, result.value());
}

TEST_F(ResourcesCtsTest, TestFractionalDimension) {
    int32_t res_id = 0x7f040002;
    
    // Use TypedValue::complex_to_float logic in reverse or just test a known complex value
    // Let's test 1.5dp on 2.0 density -> 3.0px
    TypedValue tv;
    tv.type = TypedValue::TYPE_DIMENSION;
    // 1.5 is 3 * 1/2 (radix 1: 1/2^7, radix 0: 1/1)
    // 1.5 = 192 * 1/2^7
    tv.data = (192 << TypedValue::COMPLEX_MANTISSA_SHIFT) | 
              (1 << TypedValue::COMPLEX_RADIX_SHIFT) | 
              (TypedValue::COMPLEX_UNIT_DP << TypedValue::COMPLEX_UNIT_SHIFT);
    resources->add_resource(res_id, tv);
    
    metrics->density = 2.0f;
    resources->update_configuration(*config, *metrics);
    
    auto result = resources->get_dimension(res_id);
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(3.0f, result.value());
}
