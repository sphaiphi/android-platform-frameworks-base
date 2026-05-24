#pragma once

#include <android/view/IWindowSession.h>
#include <android/view/IWindow.h>
#include <map>
#include <memory>
#include <mutex>

namespace android::view {

/**
 * Server-side stub implementation of IWindowSession.
 * In a real system this would extend BnWindowSession and handle
 * Binder transactions. For host builds this provides in-process
 * window management.
 */
class WindowSession : public IWindowSession {
public:
    WindowSession() = default;
    ~WindowSession() = default;

    // --- IWindowSession implementation ---

    int add_to_display(
            std::shared_ptr<IWindow> window,
            std::shared_ptr<LayoutParams> attrs,
            int32_t view_visibility,
            int32_t layer_stack_id,
            int32_t requested_visible_types,
            std::shared_ptr<InputChannel>& out_input_channel,
            std::shared_ptr<InsetsState>& out_insets_state,
            std::shared_ptr<InsetsSourceControlArray>& out_active_controls,
            android::graphics::Rect& out_attached_frame,
            std::vector<float>& out_size_compat_scale) override;

    void remove(std::shared_ptr<IWindow> window) override;

    int relayout(
            std::shared_ptr<IWindow> window,
            std::shared_ptr<LayoutParams> attrs,
            int32_t requested_width,
            int32_t requested_height,
            int32_t view_visibility,
            int32_t flags,
            int32_t seq,
            int32_t last_sync_seq_id,
            std::shared_ptr<WindowRelayoutResult>& out_result) override;

    void finish_drawing(
            std::shared_ptr<IWindow> window,
            void* post_draw_transaction,
            int32_t seq_id) override;

    bool cancel_draw(std::shared_ptr<IWindow> window) override;
    bool out_of_memory(std::shared_ptr<IWindow> window) override;

    // --- Registration tracking ---

    [[nodiscard]] bool is_window_registered(std::shared_ptr<IWindow> window) const;
    [[nodiscard]] size_t registered_window_count() const;

private:
    mutable std::mutex mutex_;
    std::map<std::shared_ptr<IWindow>, android::graphics::Rect> registered_windows_;
};

} // namespace android::view
