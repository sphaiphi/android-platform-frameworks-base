#include <android/view/WindowManagerImpl.h>
#include <android/view/WindowManagerGlobal.h>
#include <android/view/View.h>
#include <android/view/WindowLayoutParams.h>
#include <android/view/DisplayInfo.h>
#include <memory>
#include <expected_shim.h>
#include <string>

namespace android::view {

WindowManagerImpl::WindowManagerImpl(const DisplayInfo& display)
    : m_display(display) {}

WindowManagerGlobal& WindowManagerImpl::getGlobal() const {
    return WindowManagerGlobal::getInstance();
}

std::expected<void, std::string> WindowManagerImpl::addView(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<WindowLayoutParams>& params) {
    if (!view) {
        return std::unexpected<std::string>{"view is null"};
    }
    if (!params) {
        return std::unexpected<std::string>{"layout params is null"};
    }

    try {
        getGlobal().addView(view, params, m_display);
        return std::expected<void, std::string>{};
    } catch (const std::invalid_argument& e) {
        return std::unexpected<std::string>{e.what()};
    }
}

std::expected<void, std::string> WindowManagerImpl::updateViewLayout(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<WindowLayoutParams>& params) {
    if (!view) {
        return std::unexpected<std::string>{"view is null"};
    }
    if (!params) {
        return std::unexpected<std::string>{"layout params is null"};
    }

    try {
        getGlobal().updateViewLayout(view, params);
        return std::expected<void, std::string>{};
    } catch (const std::invalid_argument& e) {
        return std::unexpected<std::string>{e.what()};
    }
}

std::expected<void, std::string> WindowManagerImpl::removeView(
    const std::shared_ptr<View>& view) {
    if (!view) {
        return std::unexpected<std::string>{"view is null"};
    }

    try {
        getGlobal().removeView(view);
        return std::expected<void, std::string>{};
    } catch (const std::invalid_argument& e) {
        return std::unexpected<std::string>{e.what()};
    }
}

DisplayInfo WindowManagerImpl::getDefaultDisplay() const {
    return m_display;
}

} // namespace android::view
