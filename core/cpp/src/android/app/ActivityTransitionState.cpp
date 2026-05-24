#include <android/app/ActivityTransitionState.h>

namespace android::app {

auto ActivityTransitionState::save_state(android::os::Bundle& out_state) -> void {
    if (!pending_exit_names_.empty()) {
        out_state.putStringArray("android:pendingExitNames", pending_exit_names_);
    }
}

auto ActivityTransitionState::read_state(const android::os::Bundle& saved_state) -> void {
    if (saved_state.containsKey("android:pendingExitNames")) {
        pending_exit_names_ = saved_state.getStringArray("android:pendingExitNames").value_or(std::vector<std::string>{});
    }
}

} // namespace android::app
