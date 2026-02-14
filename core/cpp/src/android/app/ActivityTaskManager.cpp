#include <android/app/ActivityTaskManager.h>

namespace android::app {

auto ActivityTaskManager::get_service() -> std::shared_ptr<IActivityTaskManager> {
    // TBD: Fetch from ServiceManager
    return nullptr;
}

} // namespace android::app
