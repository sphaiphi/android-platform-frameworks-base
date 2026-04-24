#include <android/util/TypedValue.h>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace android::util {

auto TypedValue::complex_to_float(int32_t data) -> float {
    // Android complex format for floats:
    // Bits 0-3: unit
    // Bits 4-5: radix
    // Bits 8-31: mantissa
    
    static const float MANTISSA_MULT[] = {
        1.0f / (1 << 0),
        1.0f / (1 << 7),
        1.0f / (1 << 15),
        1.0f / (1 << 23)
    };

    return static_cast<float>(data >> COMPLEX_MANTISSA_SHIFT) 
           * MANTISSA_MULT[(data >> COMPLEX_RADIX_SHIFT) & COMPLEX_RADIX_MASK];
}

auto TypedValue::complex_to_dimension(int32_t data, const DisplayMetrics& metrics) -> float {
    float value = complex_to_float(data);
    int32_t unit = (data >> COMPLEX_UNIT_SHIFT) & COMPLEX_UNIT_MASK;

    switch (unit) {
        case COMPLEX_UNIT_PX:
            return value;
        case COMPLEX_UNIT_DP:
            return value * metrics.density;
        case COMPLEX_UNIT_SP:
            return value * metrics.scaled_density;
        case COMPLEX_UNIT_PT:
            return value * metrics.xdpi * (1.0f / 72);
        case COMPLEX_UNIT_IN:
            return value * metrics.xdpi;
        case COMPLEX_UNIT_MM:
            return value * metrics.xdpi * (1.0f / 25.4f);
        default:
            return 0;
    }
}

auto TypedValue::coerce_to_string() const -> std::string {
    if (type == TYPE_STRING) {
        return string_value;
    }
    if (type == TYPE_INT_BOOLEAN) {
        return data != 0 ? "true" : "false";
    }
    if (type == TYPE_INT_DEC) {
        return std::to_string(data);
    }
    if (type == TYPE_INT_HEX) {
        std::stringstream ss;
        ss << "0x" << std::uppercase << std::hex << data;
        return ss.str();
    }
    if (type >= TYPE_INT_DEC && type <= TYPE_INT_HEX) {
        return std::to_string(data);
    }
    return "";
}

} // namespace android::util
