#pragma once

#include <android/os/Bundle.h>
#include <memory>

namespace android::app {

class ActivityOptions {
public:
    ActivityOptions() = default;
    
    static auto make_custom_animation(int enter_res_id, int exit_res_id) -> std::shared_ptr<ActivityOptions>;
    
    auto to_bundle() const -> android::os::Bundle;

private:
    android::os::Bundle bundle_;
};

} // namespace android::app
