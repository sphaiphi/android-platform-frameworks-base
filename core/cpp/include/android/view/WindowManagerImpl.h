#pragma once

#include <android/view/WindowManager.h>
#include <android/view/DisplayInfo.h>
#include <memory>

namespace android::view {

class WindowManagerGlobal;

/**
 * Thin delegator to WindowManagerGlobal singleton.
 * Constructed per-display, mirrors Java's WindowManagerImpl.
 */
class WindowManagerImpl : public WindowManager {
public:
    explicit WindowManagerImpl(const DisplayInfo& display);
    ~WindowManagerImpl() override = default;

    // Non-copyable
    WindowManagerImpl(const WindowManagerImpl&) = delete;
    WindowManagerImpl& operator=(const WindowManagerImpl&) = delete;

    std::expected<void, std::string> addView(
        const std::shared_ptr<View>& view,
        const std::shared_ptr<WindowLayoutParams>& params) override;

    std::expected<void, std::string> updateViewLayout(
        const std::shared_ptr<View>& view,
        const std::shared_ptr<WindowLayoutParams>& params) override;

    std::expected<void, std::string> removeView(
        const std::shared_ptr<View>& view) override;

    DisplayInfo getDefaultDisplay() const override;

private:
    WindowManagerGlobal& getGlobal() const;
    DisplayInfo m_display;
};

} // namespace android::view
