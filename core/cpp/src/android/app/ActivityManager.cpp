#include <android/app/ActivityManager.h>

namespace android::app {

auto ActivityManager::get_running_app_processes() -> std::vector<RunningAppProcessInfo> {
    // TBD: Use IActivityManager to fetch actual list
    return {};
}

void ActivityManager::get_my_memory_state(RunningAppProcessInfo* out_info) {
    if (out_info) {
        out_info->pid = 0; // TBD: Get current pid
    }
}

auto ActivityManager::get_service() -> std::shared_ptr<IActivityManager> {
    // TBD: Fetch from ServiceManager
    return nullptr;
}

} // namespace android::app
