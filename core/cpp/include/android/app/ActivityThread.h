#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <android/os/Handler.h>
#include <android/os/Looper.h>
#include <android/app/Instrumentation.h>
#include <android/content/Intent.h>

namespace android::app {

/**
 * Manages the execution of the main thread in an application process.
 * 
 * ActivityThread is the entry point for an Android application process.
 * It coordinates the application lifecycle, activity management, and message processing.
 */
class ActivityThread {
public:
    /**
     * Bookkeeping for an active activity.
     */
    struct ActivityClientRecord {
        std::shared_ptr<Activity> activity;
        std::shared_ptr<android::content::Intent> intent;
        bool paused{false};
        bool stopped{false};
        bool hide_for_now{false};
    };

    /**
     * The main handler for the ActivityThread.
     * Processes messages related to activity lifecycles and application state.
     */
    class H : public android::os::Handler {
    public:
        using android::os::Handler::Handler;
        void handle_message(const android::os::Message& msg) override;
        
        static constexpr int BIND_APPLICATION = 110;
        static constexpr int LAUNCH_ACTIVITY = 100;
    };

    ActivityThread();
    ~ActivityThread() = default;

    /**
     * Entry point for system process initialization.
     */
    static auto system_main() -> std::shared_ptr<ActivityThread>;

    /**
     * Retrieve the current process's ActivityThread.
     */
    static auto current_activity_thread() -> std::shared_ptr<ActivityThread>;

    /**
     * Attach the thread to the system.
     */
    void attach(bool system);

    /**
     * Detach the thread from the system.
     */
    void detach();

    /**
     * Bind an application to this process.
     * @param package_name The package name of the application.
     */
    void bind_application(const std::string& package_name);

    /**
     * Handle the launch of an activity.
     */
    void handle_launch_activity(std::shared_ptr<ActivityClientRecord> r);

    /**
     * Handle the resumption of an activity.
     */
    void handle_resume_activity(void* token, bool final_state_request, bool is_forward);

    /**
     * Handle the pausing of an activity.
     */
    void handle_pause_activity(void* token, bool finished, bool user_leaving, int config_changes);

    /**
     * Get the name of the current process.
     */
    [[nodiscard]] auto get_process_name() const -> std::string { return bound_package_name_; }

private:
    static std::shared_ptr<ActivityThread> s_current_activity_thread;
    std::string bound_package_name_;
    std::shared_ptr<H> h_;
    std::shared_ptr<Instrumentation> m_instrumentation;
    std::unordered_map<void*, std::shared_ptr<ActivityClientRecord>> m_activities;
};

} // namespace android::app
