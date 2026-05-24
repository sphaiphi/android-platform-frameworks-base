#include <android/app/Instrumentation.h>
#include <android/app/ActivityManager.h>

namespace android::app {

Instrumentation::Instrumentation() = default;

auto Instrumentation::new_activity(const std::string& class_name) -> std::shared_ptr<Activity> {
    // In a real system, this would use reflection/factory based on class_name.
    // For now, it returns a base Activity.
    return std::make_shared<Activity>();
}

void Instrumentation::call_activity_on_create(std::shared_ptr<Activity> activity, const android::os::Bundle& icicle) {
    if (activity) {
        activity->perform_create(icicle);
    }
}

void Instrumentation::call_activity_on_start(std::shared_ptr<Activity> activity) {
    if (activity) {
        activity->perform_start();
    }
}

void Instrumentation::call_activity_on_resume(std::shared_ptr<Activity> activity) {
    if (activity) {
        activity->perform_resume();
    }
}

void Instrumentation::call_activity_on_pause(std::shared_ptr<Activity> activity) {
    if (activity) {
        activity->perform_pause();
    }
}

void Instrumentation::call_activity_on_stop(std::shared_ptr<Activity> activity) {
    if (activity) {
        activity->perform_stop();
    }
}

void Instrumentation::call_activity_on_destroy(std::shared_ptr<Activity> activity) {
    if (activity) {
        activity->perform_destroy();
    }
}

auto Instrumentation::exec_start_activity(
    const std::shared_ptr<Context>& who,
    const std::shared_ptr<android::os::IBinder>& context_thread,
    const std::shared_ptr<android::os::IBinder>& token,
    const std::shared_ptr<Activity>& target,
    const android::content::Intent& intent,
    int32_t request_code,
    std::optional<android::os::Bundle> options) -> int32_t {
    
    // TBD: Call ActivityTaskManager to start activity
    return 0; // START_SUCCESS
}

} // namespace android::app
