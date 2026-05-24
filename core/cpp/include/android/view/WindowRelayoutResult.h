#pragma once

#include <android/graphics/Rect.h>
#include <android/view/InsetsState.h>
#include <android/view/Surface.h>
#include <memory>

namespace android::view {

/**
 * Result returned by IWindowSession.relayout().
 * Contains the negotiated window frames, the Surface for drawing,
 * and the current insets state.
 */
struct WindowRelayoutResult {
    android::graphics::Rect frames;
    std::shared_ptr<Surface> surface;
    int32_t seq{0};
    std::optional<InsetsState> insets_state;
};

} // namespace android::view
