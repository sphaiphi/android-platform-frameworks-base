#include <android/app/Activity.h>

namespace android::app {

auto Activity::set_content_view(int layout_res_id) -> void {
    // TBD: Delegate to Window
    (void)layout_res_id; // Suppress unused parameter warning
}

auto Activity::finish() -> void {
    // TBD: Delegate to ActivityThread/ActivityClient
}

auto Activity::perform_create(const android::os::Bundle& icicle) -> void {
    state_ = ActivityState::created;
    on_create(icicle);
}

auto Activity::perform_start() -> void {
    state_ = ActivityState::started;
    on_start();
}

auto Activity::perform_resume() -> void {
    state_ = ActivityState::resumed;
    on_resume();
}

auto Activity::perform_pause() -> void {
    state_ = ActivityState::paused;
    on_pause();
}

auto Activity::perform_stop() -> void {
    state_ = ActivityState::stopped;
    on_stop();
}

auto Activity::perform_destroy() -> void {
    state_ = ActivityState::destroyed;
    on_destroy();
}

} // namespace android::app
