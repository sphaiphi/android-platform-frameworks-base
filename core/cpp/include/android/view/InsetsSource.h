#pragma once

#include <android/graphics/Rect.h>
#include <cstdint>
#include <optional>
#include <vector>

namespace android::view {

/**
 * Describes a single insets source (e.g., status bar, navigation bar, IME).
 */
struct InsetsSource {
    static constexpr int32_t SIDE_TOP = 1;
    static constexpr int32_t SIDE_LEFT = 2;
    static constexpr int32_t SIDE_RIGHT = 4;
    static constexpr int32_t SIDE_BOTTOM = 8;

    int32_t id{0};
    int32_t type{0};
    android::graphics::Rect frame;
    std::optional<android::graphics::Rect> visible_frame;
    bool visible{false};
    int32_t flags{0};
    int32_t side_hint{0};
    std::vector<android::graphics::Rect> bounding_rects;
};

} // namespace android::view
