#include <android/app/ActivityOptions.h>

namespace android::app {

auto ActivityOptions::make_custom_animation(int enter_res_id, int exit_res_id) -> std::shared_ptr<ActivityOptions> {
    auto options = std::make_shared<ActivityOptions>();
    options->bundle_.putInt("android:activity.animType", 1); // ANIM_CUSTOM
    options->bundle_.putInt("android:activity.animEnterRes", enter_res_id);
    options->bundle_.putInt("android:activity.animExitRes", exit_res_id);
    return options;
}

auto ActivityOptions::to_bundle() const -> android::os::Bundle {
    return bundle_;
}

} // namespace android::app
