#include <gtest/gtest.h>
#include <android/util/TypedValue.h>

using namespace android::util;

TEST(TypedValueTest, CoerceToStringBoolean) {
    TypedValue tv;
    tv.type = TypedValue::TYPE_INT_BOOLEAN;
    tv.data = 1;
    EXPECT_EQ(tv.coerce_to_string(), "true");
    
    tv.data = 0;
    EXPECT_EQ(tv.coerce_to_string(), "false");
}

TEST(TypedValueTest, CoerceToStringInt) {
    TypedValue tv;
    tv.type = TypedValue::TYPE_INT_DEC;
    tv.data = 42;
    EXPECT_EQ(tv.coerce_to_string(), "42");
    
    tv.type = TypedValue::TYPE_INT_HEX;
    tv.data = 0xABC;
    // Android hex strings are usually uppercase with 0x
    EXPECT_EQ(tv.coerce_to_string(), "0xABC");
}

TEST(TypedValueTest, ComplexToDimension) {
    DisplayMetrics dm;
    dm.density = 2.0f; // xhdpi
    
    // 10dp encoded in complex format
    // Mantissa: 10
    // Radix: 23p0 (0)
    // Unit: DP (1)
    int32_t complex_data = (10 << TypedValue::COMPLEX_MANTISSA_SHIFT) | 
                           (0 << TypedValue::COMPLEX_RADIX_SHIFT) |
                           (TypedValue::COMPLEX_UNIT_DP << TypedValue::COMPLEX_UNIT_SHIFT);
    
    float px = TypedValue::complex_to_dimension(complex_data, dm);
    EXPECT_FLOAT_EQ(px, 20.0f);
}
