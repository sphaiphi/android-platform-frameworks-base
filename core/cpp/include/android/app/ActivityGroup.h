#pragma once

#include <android/app/Activity.h>

namespace android::app {

class LocalActivityManager;

class ActivityGroup : public Activity {
public:
    ActivityGroup() = default;
    
    auto get_current_activity() -> std::shared_ptr<Activity>;
    auto get_local_activity_manager() -> std::shared_ptr<LocalActivityManager>;

protected:
    void on_create(const android::os::Bundle& saved_instance_state) override;
    void on_resume() override;
    void on_pause() override;
    void on_stop() override;
    void on_destroy() override;

private:
    std::shared_ptr<LocalActivityManager> local_activity_manager_;
};

} // namespace android::app
