#pragma once

#include <string>
#include <map>
#include <cstdint>

namespace android::app {

/**
 * Describes details about an application process startup.
 */
class ApplicationStartInfo {
public:
    enum StartupState {
        STARTUP_STATE_UNDEFINED = 0,
        STARTUP_STATE_STARTED = 1,
        STARTUP_STATE_ERROR = 2,
        STARTUP_STATE_FIRST_FRAME_DRAWN = 3
    };

    enum StartReason {
        START_REASON_UNDEFINED = 0,
        START_REASON_ALARM = 1,
        START_REASON_BOOT_COMPLETE = 2,
        START_REASON_BROADCAST = 3,
        START_REASON_LAUNCHER = 7,
        START_REASON_SERVICE = 9,
        START_REASON_START_ACTIVITY = 10
    };

    enum StartType {
        START_TYPE_UNDEFINED = 0,
        START_TYPE_COLD = 1,
        START_TYPE_WARM = 2,
        START_TYPE_HOT = 3
    };

    ApplicationStartInfo() = default;

    auto set_startup_state(StartupState state) -> void { startup_state_ = state; }
    [[nodiscard]] auto get_startup_state() const noexcept -> StartupState { return startup_state_; }

    auto set_pid(int pid) -> void { pid_ = pid; }
    [[nodiscard]] auto get_pid() const noexcept -> int { return pid_; }

    auto set_package_name(const std::string& packageName) -> void { package_name_ = packageName; }
    [[nodiscard]] auto get_package_name() const -> const std::string& { return package_name_; }

    auto set_reason(StartReason reason) -> void { reason_ = reason; }
    [[nodiscard]] auto get_reason() const noexcept -> StartReason { return reason_; }

    auto set_start_type(StartType type) -> void { start_type_ = type; }
    [[nodiscard]] auto get_start_type() const noexcept -> StartType { return start_type_; }

    auto add_startup_timestamp(int key, int64_t timestampNs) -> void {
        startup_timestamps_ns_[key] = timestampNs;
    }
    [[nodiscard]] auto get_startup_timestamps() const -> const std::map<int, int64_t>& {
        return startup_timestamps_ns_;
    }

private:
    StartupState startup_state_{STARTUP_STATE_UNDEFINED};
    int pid_{0};
    std::string package_name_;
    StartReason reason_{START_REASON_UNDEFINED};
    StartType start_type_{START_TYPE_UNDEFINED};
    std::map<int, int64_t> startup_timestamps_ns_;
};

} // namespace android::app
