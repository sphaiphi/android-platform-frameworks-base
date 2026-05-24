#include <gtest/gtest.h>
#include <android/content/res/Resources.h>
#include <android/util/TypedValue.h>

using namespace android::content::res;
using namespace android::util;

class ResourcesTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto assets = std::make_shared<AssetManager>();
        auto metrics = std::make_shared<DisplayMetrics>();
        metrics->density = 2.0f; // xhdpi
        auto config = std::make_shared<Configuration>();
        
        resources = std::make_unique<Resources>(assets, metrics, config);
    }

    std::unique_ptr<Resources> resources;
};

TEST_F(ResourcesTest, GetString) {
    TypedValue tv;
    tv.type = TypedValue::TYPE_STRING;
    tv.string_value = "Hello World";
    
    int32_t res_id = 0x7f010001;
    resources->add_resource(res_id, tv);
    
    auto result = resources->get_string(res_id);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "Hello World");
}

TEST_F(ResourcesTest, GetDimension) {
    TypedValue tv;
    tv.type = TypedValue::TYPE_DIMENSION;
    // 10dp
    tv.data = (10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | 
              (TypedValue::COMPLEX_UNIT_DP << TypedValue::COMPLEX_UNIT_SHIFT);
    
    int32_t res_id = 0x7f020001;
    resources->add_resource(res_id, tv);
    
    auto result = resources->get_dimension(res_id);
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value(), 20.0f);
}

TEST_F(ResourcesTest, NotFound) {
    auto result = resources->get_string(0x7f010002);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), ResourceError::NotFound);
}
