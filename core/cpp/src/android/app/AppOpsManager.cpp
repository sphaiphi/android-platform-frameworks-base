#include <android/app/AppOpsManager.h>

namespace android::app {

AppOpsManager::AppOpsManager() : service_(nullptr) {}

auto AppOpsManager::check_op(int32_t op, int32_t uid, const std::string& package_name) -> int32_t {
    // TBD: Call IAppOpsService
    return MODE_ALLOWED;
}

auto AppOpsManager::note_op(int32_t op, int32_t uid, const std::string& package_name, const std::string& attribution_tag, const std::string& message) -> int32_t {
    // TBD: Call IAppOpsService
    return MODE_ALLOWED;
}

auto AppOpsManager::start_op(int32_t op, int32_t uid, const std::string& package_name, bool attribution_chain_id, const std::string& attribution_tag, const std::string& message, int32_t attribution_flags, int32_t attribution_chain_id_int) -> int32_t {
    // TBD: Call IAppOpsService
    return MODE_ALLOWED;
}

void AppOpsManager::finish_op(int32_t op, int32_t uid, const std::string& package_name, const std::string& attribution_tag) {
    // TBD: Call IAppOpsService
}

} // namespace android::app
