#include <android/view/WindowManager.h>
#include <android/view/WindowLayoutParams.h>
#include <android/view/WindowManagerGlobal.h>
#include <android/view/DisplayInfo.h>
#include <memory>
#include <expected_shim.h>

namespace android::view {

std::expected<void, std::string> WindowManager::addView(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<WindowLayoutParams>& params) {
    auto& global = WindowManagerGlobal::getInstance();
    global.addView(view, params, getDefaultDisplay());
    return std::expected<void, std::string>{};
}

std::expected<void, std::string> WindowManager::updateViewLayout(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<WindowLayoutParams>& params) {
    auto& global = WindowManagerGlobal::getInstance();
    global.updateViewLayout(view, params);
    return std::expected<void, std::string>{};
}

std::expected<void, std::string> WindowManager::removeView(const std::shared_ptr<View>& view) {
    auto& global = WindowManagerGlobal::getInstance();
    global.removeView(view);
    return std::expected<void, std::string>{};
}

DisplayInfo WindowManager::getDefaultDisplay() const {
    return WindowManagerGlobal::getInstance().getDefaultDisplay();
}

} // namespace android::view
