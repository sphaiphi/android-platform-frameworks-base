#pragma once

#include <string>
#include <vector>
#include <memory>

namespace android::app {

class IActivityManager {
public:
    virtual ~IActivityManager() = default;
};

class ActivityManager {
public:
    class TaskDescription {
    public:
        TaskDescription() = default;
        explicit TaskDescription(const std::string& label) : label_(label) {}
        
        auto get_label() const -> const std::string& { return label_; }
        
    private:
        std::string label_;
    };

    struct RunningAppProcessInfo {
        std::string processName;
        int pid;
        int uid;
    };

    struct RunningTaskInfo {
        int taskId;
    };

    ActivityManager() = default;

    auto get_running_app_processes() -> std::vector<RunningAppProcessInfo>;

    /**
     * Return global information about memory state.
     */
    void get_my_memory_state(RunningAppProcessInfo* out_info);

    /**
     * @hide
     */
    static auto get_service() -> std::shared_ptr<IActivityManager>;
};

} // namespace android::app