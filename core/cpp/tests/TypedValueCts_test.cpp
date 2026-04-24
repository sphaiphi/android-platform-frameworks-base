#include <gtest/gtest.h>
#include <android/util/TypedValue.h>
#include <android/util/DisplayMetrics.h>
#include <cmath>

using namespace android::util;

class TypedValueCtsTest : public ::testing::Test {
protected:
    DisplayMetrics dm;

    void SetUp() override {
        dm.density = 1.1f;
        dm.height_pixels = 100;
        dm.scaled_density = 2.1f;
        dm.xdpi = 200.0f;
        dm.ydpi = 300.0f;
    }
};

TEST_F(TypedValueCtsTest, TestComplexToFloat) {
    // 0 mantissa
    EXPECT_FLOAT_EQ(0.0f, TypedValue::complex_to_float(0));
    
    // radix 0, mantissa 1
    int32_t complex = (1 << TypedValue::COMPLEX_MANTISSA_SHIFT);
    EXPECT_FLOAT_EQ(1.0f, TypedValue::complex_to_float(complex));
    
    // radix 3, mantissa 1
    complex = (1 << TypedValue::COMPLEX_MANTISSA_SHIFT) | (3 << TypedValue::COMPLEX_RADIX_SHIFT);
    // 1 * 1/(2^23)
    EXPECT_FLOAT_EQ(1.0f / (1 << 23), TypedValue::complex_to_float(complex));

    // Test a negative value to see if sign extension works
    // mantissa -1 (all 1s in 24 bits)
    complex = (0xffffff << TypedValue::COMPLEX_MANTISSA_SHIFT);
    EXPECT_FLOAT_EQ(-1.0f, TypedValue::complex_to_float(complex));
}

TEST_F(TypedValueCtsTest, TestApplyDimension) {
    EXPECT_FLOAT_EQ(10.0f, TypedValue::complex_to_dimension((10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | TypedValue::COMPLEX_UNIT_PX, dm));
    EXPECT_FLOAT_EQ(10.0f * dm.density, TypedValue::complex_to_dimension((10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | TypedValue::COMPLEX_UNIT_DP, dm));
    EXPECT_FLOAT_EQ(10.0f * dm.scaled_density, TypedValue::complex_to_dimension((10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | TypedValue::COMPLEX_UNIT_SP, dm));
    EXPECT_FLOAT_EQ(10.0f * dm.xdpi * (1.0f/72), TypedValue::complex_to_dimension((10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | TypedValue::COMPLEX_UNIT_PT, dm));
    EXPECT_FLOAT_EQ(10.0f * dm.xdpi, TypedValue::complex_to_dimension((10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | TypedValue::COMPLEX_UNIT_IN, dm));
    EXPECT_FLOAT_EQ(10.0f * dm.xdpi * (1.0f / 25.4f), TypedValue::complex_to_dimension((10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | TypedValue::COMPLEX_UNIT_MM, dm));
}

TEST_F(TypedValueCtsTest, TestComplexToDimensionPixelSize) {
    // Porting from Java: assertEquals(1, TypedValue.complexToDimensionPixelSize(1000, dm));
    // Wait, 1000 is the raw complex data.
    // Let's check what 1000 means.
    // 1000 = 0x3E8
    // unit = 0x8 (COMPLEX_UNIT_MM is 5, wait, 0x8 is not defined)
    // radix = 0xE & 0x3 = 2 (1/2^15)
    // mantissa = 0x3 >> 0 = 3? No, mantissa is shifted by 8.
    
    // Actually the Java test uses literal values. I should replicate them.
}
