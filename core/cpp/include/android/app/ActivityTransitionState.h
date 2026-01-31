#pragma once

#include <android/os/Bundle.h>
#include <vector>
#include <string>

namespace android::app {

class ActivityTransitionState {
public:
    ActivityTransitionState() = default;

    auto save_state(android::os::Bundle& out_state) -> void;
    auto read_state(const android::os::Bundle& saved_state) -> void;

private:
    std::vector<std::string> pending_exit_names_;
};

} // namespace android::app
