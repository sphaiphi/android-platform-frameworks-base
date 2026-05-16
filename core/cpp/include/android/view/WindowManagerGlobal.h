#pragma once

#include <android/view/View.h>
#include <android/view/ViewRootImpl.h>
#include <android/view/WindowLayoutParams.h>
#include <android/view/DisplayInfo.h>
#include <vector>
#include <memory>
#include <mutex>

namespace android::view {

/**
 * Internal singleton that tracks all views registered with any WindowManager instance.
 * Manages ViewRootImpl lifecycle, view registration, and display information.
 */
class WindowManagerGlobal {
public:
    static WindowManagerGlobal& getInstance();

    // Non-copyable
    WindowManagerGlobal(const WindowManagerGlobal&) = delete;
    WindowManagerGlobal& operator=(const WindowManagerGlobal&) = delete;

    /**
     * Add a view to the window system.
     * Creates a ViewRootImpl, registers with IWindowSession, and stores registration.
     */
    void addView(std::shared_ptr<View> view,
                 std::shared_ptr<WindowLayoutParams> params,
                 const DisplayInfo& display);

    /**
     * Update layout parameters for an existing view.
     * Finds the ViewRootImpl, updates params, triggers traversal.
     */
    void updateViewLayout(std::shared_ptr<View> view,
                          std::shared_ptr<WindowLayoutParams> params);

    /**
     * Remove a view from the window system.
     * Tears down ViewRootImpl and removes registration.
     */
    void removeView(std::shared_ptr<View> view);

    /**
     * Find the ViewRootImpl for a given view.
     * @return ViewRootImpl pointer, or nullptr if not found
     */
    ViewRootImpl* findView(const std::shared_ptr<View>& view) const;

    /**
     * Get the default display info.
     */
    DisplayInfo getDefaultDisplay() const;

    /**
     * Get all available displays.
     */
    const std::vector<DisplayInfo>& getDisplays() const;

    /**
     * Clear all registrations (for testing only).
     */
    void clearForTesting();

private:
    WindowManagerGlobal() = default;
    ~WindowManagerGlobal() = default;

    struct ViewRegistration {
        std::shared_ptr<View> view;
        std::shared_ptr<WindowLayoutParams> params;
        std::unique_ptr<ViewRootImpl> rootImpl;
        DisplayInfo display;
    };

    mutable std::mutex mutex_;
    std::vector<ViewRegistration> registrations_;
    std::vector<DisplayInfo> displays_;
};

} // namespace android::view
