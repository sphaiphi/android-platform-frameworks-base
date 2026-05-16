#include <android/view/WindowManagerGlobal.h>
#include <android/view/ViewRootImpl.h>
#include <android/view/WindowSession.h>
#include <android/view/IWindow.h>
#include <algorithm>
#include <stdexcept>

namespace android::view {

WindowManagerGlobal& WindowManagerGlobal::getInstance() {
    static WindowManagerGlobal instance;
    return instance;
}

void WindowManagerGlobal::addView(std::shared_ptr<View> view,
                                   std::shared_ptr<WindowLayoutParams> params,
                                   const DisplayInfo& display) {
    if (!view) {
        throw std::invalid_argument("view is null");
    }
    if (!params) {
        throw std::invalid_argument("layout params is null");
    }

    std::lock_guard<std::mutex> lock(mutex_);

    // Check for duplicate registration
    for (const auto& reg : registrations_) {
        if (reg.view == view) {
            throw std::invalid_argument("view already added to another window");
        }
    }

    // Create ViewRootImpl and register with IWindowSession
    auto rootImpl = std::make_unique<ViewRootImpl>();
    rootImpl->set_view(view);
    rootImpl->set_window_session(std::make_shared<WindowSession>());

    ViewRegistration reg;
    reg.view = std::move(view);
    reg.params = std::move(params);
    reg.rootImpl = std::move(rootImpl);
    reg.display = display;
    registrations_.push_back(std::move(reg));
}

void WindowManagerGlobal::updateViewLayout(std::shared_ptr<View> view,
                                            std::shared_ptr<WindowLayoutParams> params) {
    if (!view) {
        throw std::invalid_argument("view is null");
    }
    if (!params) {
        throw std::invalid_argument("layout params is null");
    }

    std::lock_guard<std::mutex> lock(mutex_);

    for (auto& reg : registrations_) {
        if (reg.view == view) {
            reg.params = std::move(params);
            reg.rootImpl->perform_traversals();
            return;
        }
    }
    throw std::invalid_argument("view is not added to this window");
}

void WindowManagerGlobal::removeView(std::shared_ptr<View> view) {
    if (!view) {
        throw std::invalid_argument("view is null");
    }

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = std::find_if(registrations_.begin(), registrations_.end(),
        [&view](const ViewRegistration& reg) { return reg.view == view; });
    if (it == registrations_.end()) {
        throw std::invalid_argument("view is not added to this window");
    }
    registrations_.erase(it);
}

ViewRootImpl* WindowManagerGlobal::findView(const std::shared_ptr<View>& view) const {
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& reg : registrations_) {
        if (reg.view == view) {
            return reg.rootImpl.get();
        }
    }
    return nullptr;
}

DisplayInfo WindowManagerGlobal::getDefaultDisplay() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (displays_.empty()) {
        // Default primary display
        return DisplayInfo{1080, 1920, 0};
    }
    return displays_[0];
}

const std::vector<DisplayInfo>& WindowManagerGlobal::getDisplays() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return displays_;
}

void WindowManagerGlobal::clearForTesting() {
    std::lock_guard<std::mutex> lock(mutex_);
    registrations_.clear();
    displays_.clear();
}

} // namespace android::view
