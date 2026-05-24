#pragma once

#include <android/graphics/Rect.h>
#include <android/view/InputChannel.h>
#include <android/view/InsetsSourceControlArray.h>
#include <android/view/InsetsState.h>
#include <android/view/WindowRelayoutResult.h>
#include <android/view/LayoutParams.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace android::view {

class IWindow;

/**
 * Client-side interface to the Window Manager Service session.
 * Mirrors the IWindowSession AIDL interface.
 * Only the core methods required by ViewRootImpl are implemented.
 */
class IWindowSession {
public:
    virtual ~IWindowSession() = default;

    // --- Window Lifecycle ---

    virtual int add_to_display(
            std::shared_ptr<IWindow> window,
            std::shared_ptr<LayoutParams> attrs,
            int32_t view_visibility,
            int32_t layer_stack_id,
            int32_t requested_visible_types,
            std::shared_ptr<InputChannel>& out_input_channel,
            std::shared_ptr<InsetsState>& out_insets_state,
            std::shared_ptr<InsetsSourceControlArray>& out_active_controls,
            android::graphics::Rect& out_attached_frame,
            std::vector<float>& out_size_compat_scale) = 0;

    virtual void remove(std::shared_ptr<IWindow> /*window*/) = 0;

    // --- Layout & Surface ---

    virtual int relayout(
            std::shared_ptr<IWindow> window,
            std::shared_ptr<LayoutParams> attrs,
            int32_t requested_width,
            int32_t requested_height,
            int32_t view_visibility,
            int32_t flags,
            int32_t seq,
            int32_t last_sync_seq_id,
            std::shared_ptr<WindowRelayoutResult>& out_result) = 0;

    // --- Drawing Sync ---

    virtual void finish_drawing(
            std::shared_ptr<IWindow> window,
            void* /*post_draw_transaction*/,
            int32_t seq_id) = 0;

    // --- State Queries ---

    virtual bool cancel_draw(std::shared_ptr<IWindow> window) = 0;
    virtual bool out_of_memory(std::shared_ptr<IWindow> window) = 0;
};

} // namespace android::view
