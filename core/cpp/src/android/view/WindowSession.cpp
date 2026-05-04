#include <android/view/WindowSession.h>
#include <android/view/IWindow.h>

namespace android::view {

int WindowSession::add_to_display(
        std::shared_ptr<IWindow> window,
        std::shared_ptr<LayoutParams> /*attrs*/,
        int32_t /*view_visibility*/,
        int32_t /*layer_stack_id*/,
        int32_t /*requested_visible_types*/,
        std::shared_ptr<InputChannel>& out_input_channel,
        std::shared_ptr<InsetsState>& out_insets_state,
        std::shared_ptr<InsetsSourceControlArray>& out_active_controls,
        android::graphics::Rect& out_attached_frame,
        std::vector<float>& out_size_compat_scale) {

    std::lock_guard<std::mutex> lock(mutex_);
    if (window) {
        registered_windows_[window] = android::graphics::Rect{0, 0, 0, 0};
    }

    out_insets_state = std::make_shared<InsetsState>();
    out_active_controls = std::make_shared<InsetsSourceControlArray>();

    return 0;
}

void WindowSession::remove(std::shared_ptr<IWindow> window) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (window) {
        registered_windows_.erase(window);
    }
}

int WindowSession::relayout(
        std::shared_ptr<IWindow> window,
        std::shared_ptr<LayoutParams> attrs,
        int32_t requested_width,
        int32_t requested_height,
        int32_t /*view_visibility*/,
        int32_t /*flags*/,
        int32_t seq,
        int32_t /*last_sync_seq_id*/,
        std::shared_ptr<WindowRelayoutResult>& out_result) {

    out_result = std::make_shared<WindowRelayoutResult>();

    int32_t width = requested_width > 0 ? requested_width : 1080;
    int32_t height = requested_height > 0 ? requested_height : 1920;

    if (attrs && attrs->width != -1 && attrs->height != -1) {
        width = attrs->width > 0 ? attrs->width : width;
        height = attrs->height > 0 ? attrs->height : height;
    }

    out_result->frames = android::graphics::Rect{0, 0, width, height};
    out_result->seq = seq;

    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (window) {
            registered_windows_[window] = out_result->frames;
        }
    }

    InsetsState state;
    state.display_frame = android::graphics::Rect{0, 0, width, height};
    state.seq = seq;
    out_result->insets_state = state;

    return 0;
}

void WindowSession::finish_drawing(
        std::shared_ptr<IWindow> /*window*/,
        void* /*post_draw_transaction*/,
        int32_t /*seq_id*/) {
    // No-op for host build
}

bool WindowSession::cancel_draw(std::shared_ptr<IWindow> /*window*/) {
    return false;
}

bool WindowSession::out_of_memory(std::shared_ptr<IWindow> /*window*/) {
    return false;
}

bool WindowSession::is_window_registered(std::shared_ptr<IWindow> window) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return registered_windows_.find(window) != registered_windows_.end();
}

size_t WindowSession::registered_window_count() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return registered_windows_.size();
}

} // namespace android::view
