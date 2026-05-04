#pragma once

#include <android/graphics/Rect.h>
#include <cstdint>

namespace android::view {

/**
 * Bounds and orientation of the privacy indicator for a given display.
 */
struct PrivacyIndicatorBounds {
    android::graphics::Rect bounds;
    int32_t rotation{0};
    int32_t display_id{0};
};

} // namespace android::view
