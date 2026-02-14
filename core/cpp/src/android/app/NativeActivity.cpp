#include <android/app/NativeActivity.h>

namespace android::app {

NativeActivity::NativeActivity() : Activity() {}

auto NativeActivity::on_create(const android::os::Bundle& saved_instance_state) -> void {
    Activity::on_create(saved_instance_state);
}

auto NativeActivity::on_start() -> void {
    Activity::on_start();
}

auto NativeActivity::on_resume() -> void {
    Activity::on_resume();
}

auto NativeActivity::on_pause() -> void {
    Activity::on_pause();
}

auto NativeActivity::on_stop() -> void {
    Activity::on_stop();
}

auto NativeActivity::on_destroy() -> void {
    Activity::on_destroy();
}

auto NativeActivity::on_configuration_changed(const android::content::res::Configuration& new_config) -> void {
    Activity::on_configuration_changed(new_config);
}

auto NativeActivity::on_low_memory() -> void {
    Activity::on_low_memory();
}

void NativeActivity::on_window_focus_changed(bool has_focus) {
    // TBD: Forward to native code
}

} // namespace android::app
