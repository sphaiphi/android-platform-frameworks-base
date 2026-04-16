#pragma once

#include <cstdint>

namespace android::view {

class LayoutParams {
public:
    static constexpr int32_t MATCH_PARENT = -1;
    static constexpr int32_t WRAP_CONTENT = -2;

    int32_t width;
    int32_t height;

    LayoutParams(int32_t w, int32_t h) : width(w), height(h) {}
    virtual ~LayoutParams() = default;
};

class MarginLayoutParams : public LayoutParams {
public:
    int32_t left_margin{0};
    int32_t top_margin{0};
    int32_t right_margin{0};
    int32_t bottom_margin{0};

    MarginLayoutParams(int32_t w, int32_t h) : LayoutParams(w, h) {}
    
    void set_margins(int32_t left, int32_t top, int32_t right, int32_t bottom) {
        left_margin = left;
        top_margin = top;
        right_margin = right;
        bottom_margin = bottom;
    }
};

} // namespace android::view
