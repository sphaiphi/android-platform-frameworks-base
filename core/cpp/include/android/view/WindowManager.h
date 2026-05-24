#pragma once

#include <memory>
#include <string>
#include <expected_shim.h>

namespace android::view {

class View;
class WindowLayoutParams;
struct DisplayInfo;

/**
 * Public interface for managing windows.
 * Mirrors android.view.WindowManager Java API.
 * Each instance is bound to a specific Display.
 * All state is managed by WindowManagerGlobal singleton.
 */
class WindowManager {
public:
    WindowManager() = default;
    virtual ~WindowManager() = default;

    /**
     * Add a view to the window with the specified layout parameters.
     * Creates a ViewRootImpl and registers the view with IWindowSession.
     * @param view The view to add
     * @param params Layout parameters for the view
     * @return std::expected<void, std::string> on success or error message
     */
    virtual std::expected<void, std::string> addView(
        const std::shared_ptr<View>& view,
        const std::shared_ptr<WindowLayoutParams>& params);

    /**
     * Update the layout parameters of an existing view.
     * Triggers re-measure, re-layout, and re-draw.
     * @param view The view to update
     * @param params New layout parameters
     * @return std::expected<void, std::string> on success or error message
     */
    virtual std::expected<void, std::string> updateViewLayout(
        const std::shared_ptr<View>& view,
        const std::shared_ptr<WindowLayoutParams>& params);

    /**
     * Remove a view from the window.
     * Tears down the ViewRootImpl and releases resources.
     * @param view The view to remove
     * @return std::expected<void, std::string> on success or error message
     */
    virtual std::expected<void, std::string> removeView(const std::shared_ptr<View>& view);

    /**
     * Get the display information for the bound display.
     * @return DisplayInfo for this WindowManager's display
     */
    virtual DisplayInfo getDefaultDisplay() const;
};

} // namespace android::view
