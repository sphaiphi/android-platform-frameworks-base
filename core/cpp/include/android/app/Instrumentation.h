#pragma once

#include <memory>
#include <optional>
#include <string>
#include <android/app/Activity.h>
#include <android/os/Bundle.h>
#include <android/os/IBinder.h>
#include <android/content/Intent.h>

namespace android::app {

class ActivityThread;
class Context;

/**
 * Base class for implementing application instrumentation code.
 * 
 * Instrumentation allows you to monitor all of the interaction the system has with the application.
 * It provides hooks to intercept activity launches and drive lifecycle events.
 */
class Instrumentation {
public:
    Instrumentation();
    virtual ~Instrumentation() = default;

    /**
     * Instantiate a new Activity object.
     * @param class_name The name of the class to instantiate.
     */
    virtual auto new_activity(const std::string& class_name) -> std::shared_ptr<Activity>;
    
    /**
     * Perform calling of the activity's on_create method.
     */
    virtual void call_activity_on_create(std::shared_ptr<Activity> activity, const android::os::Bundle& icicle);

    /**
     * Perform calling of the activity's on_start method.
     */
    virtual void call_activity_on_start(std::shared_ptr<Activity> activity);

    /**
     * Perform calling of the activity's on_resume method.
     */
    virtual void call_activity_on_resume(std::shared_ptr<Activity> activity);

    /**
     * Perform calling of the activity's on_pause method.
     */
    virtual void call_activity_on_pause(std::shared_ptr<Activity> activity);

    /**
     * Perform calling of the activity's on_stop method.
     */
    virtual void call_activity_on_stop(std::shared_ptr<Activity> activity);

    /**
     * Perform calling of the activity's on_destroy method.
     */
    virtual void call_activity_on_destroy(std::shared_ptr<Activity> activity);

    /**
     * Execute the start of a new activity.
     */
    virtual auto exec_start_activity(
        const std::shared_ptr<Context>& who,
        const std::shared_ptr<android::os::IBinder>& context_thread,
        const std::shared_ptr<android::os::IBinder>& token,
        const std::shared_ptr<Activity>& target,
        const android::content::Intent& intent,
        int32_t request_code,
        std::optional<android::os::Bundle> options) -> int32_t;

private:
    // Reference to ActivityThread if needed
};

} // namespace android::app
