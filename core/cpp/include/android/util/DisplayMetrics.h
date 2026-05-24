#pragma once

#include <cstdint>

namespace android::util {

class DisplayMetrics {
public:
    static constexpr int32_t DENSITY_LOW = 120;
    static constexpr int32_t DENSITY_MEDIUM = 160;
    static constexpr int32_t DENSITY_TV = 213;
    static constexpr int32_t DENSITY_HIGH = 240;
    static constexpr int32_t DENSITY_XHIGH = 320;
    static constexpr int32_t DENSITY_XXHIGH = 480;
    static constexpr int32_t DENSITY_XXXHIGH = 640;
    static constexpr int32_t DENSITY_DEFAULT = DENSITY_MEDIUM;

    int32_t width_pixels{0};
    int32_t height_pixels{0};
    float density{1.0f};
    int32_t density_dpi{DENSITY_DEFAULT};
    float scaled_density{1.0f};
    float xdpi{static_cast<float>(DENSITY_DEFAULT)};
    float ydpi{static_cast<float>(DENSITY_DEFAULT)};

    DisplayMetrics() = default;

    auto set_to_defaults() -> void;
    
    // Static utility for unit conversion (like TypedValue.complexToDimension)
    // but often used directly or via Resources
};

} // namespace android::util
