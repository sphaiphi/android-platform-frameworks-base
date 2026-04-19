#pragma once

#include <cstdint>
#include <string>
#include <android/util/DisplayMetrics.h>

namespace android::util {

class TypedValue {
public:
    static constexpr int32_t TYPE_NULL = 0x00;
    static constexpr int32_t TYPE_REFERENCE = 0x01;
    static constexpr int32_t TYPE_ATTRIBUTE = 0x02;
    static constexpr int32_t TYPE_STRING = 0x03;
    static constexpr int32_t TYPE_FLOAT = 0x04;
    static constexpr int32_t TYPE_DIMENSION = 0x05;
    static constexpr int32_t TYPE_FRACTION = 0x06;
    static constexpr int32_t TYPE_INT_DEC = 0x10;
    static constexpr int32_t TYPE_INT_HEX = 0x11;
    static constexpr int32_t TYPE_INT_BOOLEAN = 0x12;

    static constexpr int32_t COMPLEX_UNIT_SHIFT = 0;
    static constexpr int32_t COMPLEX_UNIT_MASK = 0xf;
    static constexpr int32_t COMPLEX_UNIT_PX = 0;
    static constexpr int32_t COMPLEX_UNIT_DP = 1;
    static constexpr int32_t COMPLEX_UNIT_SP = 2;
    static constexpr int32_t COMPLEX_UNIT_PT = 3;
    static constexpr int32_t COMPLEX_UNIT_IN = 4;
    static constexpr int32_t COMPLEX_UNIT_MM = 5;

    static constexpr int32_t COMPLEX_RADIX_SHIFT = 4;
    static constexpr int32_t COMPLEX_RADIX_MASK = 0x3;
    static constexpr int32_t COMPLEX_MANTISSA_SHIFT = 8;
    static constexpr int32_t COMPLEX_MANTISSA_MASK = 0xffffff;

    int32_t type{TYPE_NULL};
    std::string string_value;
    int32_t data{0};
    int32_t asset_cookie{0};
    int32_t resource_id{0};
    uint32_t changing_configurations{0};

    TypedValue() = default;

    static auto complex_to_dimension(int32_t data, const DisplayMetrics& metrics) -> float;
    static auto complex_to_float(int32_t data) -> float;
    
    auto coerce_to_string() const -> std::string;
};

} // namespace android::util
