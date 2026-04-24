#include <android/util/TypedValue.h>
#include <android/util/DisplayMetrics.h>
#include <iostream>
#include <string>

int main() {
    // Verify Boolean Coercion
    android::util::TypedValue tv;
    tv.type = android::util::TypedValue::TYPE_INT_BOOLEAN;
    tv.data = 1;
    std::string bool_str = tv.coerce_to_string();
    std::cout << "TypedValue: Boolean(1) coerced to string = " << bool_str << std::endl;
    if (bool_str != "true") return 1;
    // Verify Dimension Conversion (10dp at xhdpi)
    android::util::DisplayMetrics dm;
    dm.density = 2.0f; // xhdpi
    int32_t complex_data = (10 << android::util::TypedValue::COMPLEX_MANTISSA_SHIFT) | 
                           (0 << android::util::TypedValue::COMPLEX_RADIX_SHIFT) |
                           (android::util::TypedValue::COMPLEX_UNIT_DP << android::util::TypedValue::COMPLEX_UNIT_SHIFT);
    
    float px = android::util::TypedValue::complex_to_dimension(complex_data, dm);
    std::cout << "TypedValue: 10dp at xhdpi = " << px << "px" << std::endl;
    if (px != 20.0f) return 2;
    std::cout << "SUCCESS: Core Data Containers (TypedValue) verification complete." << std::endl;
    return 0;
}