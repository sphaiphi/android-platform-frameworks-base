#pragma once

#include <android/graphics/Rect.h>
#include <cstdint>

namespace android::view {

/**
 * Callback interface from the Window Manager Service to the client window.
 * The client implements this interface to receive window state changes.
 * Mirrors the Java IWindow.oneway interface.
 */
class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void on_resized(const android::graphics::Rect& frames, bool report_draw) = 0;
    virtual void on_moved(int32_t new_x, int32_t new_y) = 0;
    virtual void on_dispatch_app_visibility(bool visible) = 0;
    virtual void on_dispatch_get_new_surface() {}
    virtual void on_dispatch_window_shown() {}
    virtual void on_close_system_dialogs(const std::string& /*reason*/) {}
};

} // namespace android::view
