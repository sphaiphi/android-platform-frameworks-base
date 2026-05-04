#pragma once

#include <android/graphics/Rect.h>
#include <android/view/InsetsSource.h>
#include <android/view/PrivacyIndicatorBounds.h>
#include <optional>
#include <vector>

namespace android::view {

/**
 * Describes the current state of all insets sources for a window.
 * Returned by IWindowSession.addToDisplay and IWindowSession.relayout.
 */
struct InsetsState {
    android::graphics::Rect display_frame;
    std::optional<PrivacyIndicatorBounds> privacy_indicator_bounds;
    int32_t seq{0};
    std::vector<InsetsSource> sources;
};

} // namespace android::view
