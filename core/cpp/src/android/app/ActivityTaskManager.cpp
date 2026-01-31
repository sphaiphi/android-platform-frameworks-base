#include <android/app/ActivityTaskManager.h>

namespace android::app {

auto ActivityTaskManager::getInstance() -> ActivityTaskManager& {
    static ActivityTaskManager instance;
    return instance;
}

auto ActivityTaskManager::remove_task(int task_id) -> bool {
    // TBD: Use IActivityTaskManager to remove task
    (void)task_id;
    return false;
}

} // namespace android::app
