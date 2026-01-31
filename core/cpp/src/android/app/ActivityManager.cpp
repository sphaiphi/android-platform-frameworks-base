#include <android/app/ActivityManager.h>

namespace android::app {

auto ActivityManager::get_running_app_processes() -> std::vector<RunningAppProcessInfo> {
    // TBD: Use IActivityManager to fetch actual list
    return {};
}

} // namespace android::app
