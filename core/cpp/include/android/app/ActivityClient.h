#pragma once

#include <android/os/IBinder.h>
#include <android/content/res/Configuration.h>
#include <android/content/Intent.h>
#include <android/app/ActivityManager.h>
#include <memory>

namespace android::app {

class IActivityClientController {
public:
    virtual ~IActivityClientController() = default;
    
    virtual void activityResumed(const std::shared_ptr<os::IBinder>& token, bool handleSplashScreenExit) = 0;
    virtual void activityPaused(const std::shared_ptr<os::IBinder>& token) = 0;
    virtual void activityStopped(const std::shared_ptr<os::IBinder>& token, 
                                 const os::Bundle& state,
                                 const std::string& description) = 0;
    virtual void activityDestroyed(const std::shared_ptr<os::IBinder>& token) = 0;
    virtual void finishActivity(const std::shared_ptr<os::IBinder>& token, 
                                int resultCode, 
                                const std::shared_ptr<content::Intent>& resultData, 
                                int finishTask) = 0;
};

class ActivityClient {
public:
    static auto getInstance() -> ActivityClient&;

    void activityResumed(const std::shared_ptr<os::IBinder>& token, bool handleSplashScreenExit);
    void activityPaused(const std::shared_ptr<os::IBinder>& token);
    void activityStopped(const std::shared_ptr<os::IBinder>& token, 
                         const os::Bundle& state,
                         const std::string& description);
    void activityDestroyed(const std::shared_ptr<os::IBinder>& token);
    void finishActivity(const std::shared_ptr<os::IBinder>& token, 
                        int resultCode, 
                        const std::shared_ptr<content::Intent>& resultData, 
                        int finishTask);

    auto set_interface(std::shared_ptr<IActivityClientController> interface) -> void {
        interface_ = std::move(interface);
    }

private:
    ActivityClient() = default;
    void ensure_interface_selected();
    std::shared_ptr<IActivityClientController> interface_;
};

} // namespace android::app
