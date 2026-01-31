#include <android/app/ActivityClient.h>

namespace android::app {

auto ActivityClient::getInstance() -> ActivityClient& {
    static ActivityClient instance;
    instance.ensure_interface_selected();
    return instance;
}

void ActivityClient::ensure_interface_selected() {
    if (interface_) return;
    // TBD: Fetch from ServiceManager
    // interface_ = ActivityTaskManager::getService()->getActivityClientController();
}

void ActivityClient::activityResumed(const std::shared_ptr<os::IBinder>& token, bool handleSplashScreenExit) {
    if (interface_) {
        interface_->activityResumed(token, handleSplashScreenExit);
    }
}

void ActivityClient::activityPaused(const std::shared_ptr<os::IBinder>& token) {
    if (interface_) {
        interface_->activityPaused(token);
    }
}

void ActivityClient::activityStopped(const std::shared_ptr<os::IBinder>& token, 
                                     const os::Bundle& state,
                                     const std::string& description) {
    if (interface_) {
        interface_->activityStopped(token, state, description);
    }
}

void ActivityClient::activityDestroyed(const std::shared_ptr<os::IBinder>& token) {
    if (interface_) {
        interface_->activityDestroyed(token);
    }
}

void ActivityClient::finishActivity(const std::shared_ptr<os::IBinder>& token, 
                                    int resultCode, 
                                    const std::shared_ptr<content::Intent>& resultData, 
                                    int finishTask) {
    if (interface_) {
        interface_->finishActivity(token, resultCode, resultData, finishTask);
    }
}

} // namespace android::app
