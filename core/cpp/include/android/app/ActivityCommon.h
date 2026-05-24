#pragma once

namespace android::app {

enum class ActivityError {
    invalid_state_transition,
    super_not_called,
    system_error,
    binder_error,
    service_not_found,
    invalid_token
};

} // namespace android::app
