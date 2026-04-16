#pragma once

#include <cstdint>

namespace android::view {

class Gravity {
public:
    static constexpr int32_t NO_GRAVITY = 0x0000;
    
    static constexpr int32_t TOP = 0x0030;
    static constexpr int32_t BOTTOM = 0x0050;
    static constexpr int32_t LEFT = 0x0003;
    static constexpr int32_t RIGHT = 0x0005;
    static constexpr int32_t CENTER_VERTICAL = 0x0010;
    static constexpr int32_t CENTER_HORIZONTAL = 0x0001;
    static constexpr int32_t CENTER = CENTER_VERTICAL | CENTER_HORIZONTAL;

    static constexpr int32_t FILL_VERTICAL = 0x0070;
    static constexpr int32_t FILL_HORIZONTAL = 0x0007;
    static constexpr int32_t FILL = FILL_VERTICAL | FILL_HORIZONTAL;

    static constexpr int32_t START = 0x00800003;
    static constexpr int32_t END = 0x00800005;

    static constexpr int32_t HORIZONTAL_GRAVITY_MASK = 0x0007;
    static constexpr int32_t VERTICAL_GRAVITY_MASK = 0x0070;
};

} // namespace android::view
