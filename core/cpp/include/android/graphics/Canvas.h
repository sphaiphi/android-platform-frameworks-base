#pragma once

#include <cstdint>

namespace android::graphics {

class Canvas {
public:
    virtual ~Canvas() = default;
    virtual void draw_rect(int32_t l, int32_t t, int32_t r, int32_t b) = 0;
    // Add other drawing operations as needed
};

} // namespace android::graphics
