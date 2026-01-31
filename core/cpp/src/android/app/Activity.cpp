#include <android/app/Activity.h>
#include <android/app/ActivityClient.h>
#include <stdexcept>

namespace android::app {

auto Activity::on_create(const android::os::Bundle& /*saved_instance_state*/) -> void {
    called_ = true;
}

auto Activity::on_start() -> void {
    called_ = true;
}

auto Activity::on_restart() -> void {
    called_ = true;
}

auto Activity::on_resume() -> void {
    called_ = true;
}

auto Activity::on_pause() -> void {
    called_ = true;
}

auto Activity::on_stop() -> void {
    called_ = true;
}

auto Activity::on_destroy() -> void {
    called_ = true;
}

auto Activity::on_configuration_changed(const android::content::res::Configuration& /*new_config*/) -> void {
}

auto Activity::on_low_memory() -> void {
}

auto Activity::on_trim_memory(int32_t /*level*/) -> void {
}

auto Activity::set_content_view(int layout_res_id) -> void {
    if (window_) {
        window_->set_content_view(layout_res_id);
    }
}

auto Activity::finish() -> void {
    ActivityClient::getInstance().finishActivity(token_, result_code_, nullptr, 0);
}

auto Activity::start_activity_for_result(const android::content::Intent& /*intent*/, int32_t /*request_code*/, std::optional<android::os::Bundle> /*options*/) -> void {
    // TBD: Use Instrumentation to start activity
}

auto Activity::set_result(int32_t result_code, std::optional<android::content::Intent> data) -> void {
    result_code_ = result_code;
    result_data_ = std::move(data);
}

auto Activity::perform_create(const android::os::Bundle& icicle) -> std::expected<void, ActivityError> {
    called_ = false;
    on_create(icicle);
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    state_ = ActivityState::created;
    return {};
}

auto Activity::perform_start() -> std::expected<void, ActivityError> {
    called_ = false;
    on_start();
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    state_ = ActivityState::started;
    stopped_ = false;
    return {};
}

auto Activity::perform_restart() -> std::expected<void, ActivityError> {
    called_ = false;
    on_restart();
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    stopped_ = false;
    return perform_start();
}

auto Activity::perform_resume() -> std::expected<void, ActivityError> {
    called_ = false;
    on_resume();
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    state_ = ActivityState::resumed;
    resumed_ = true;
    return {};
}

auto Activity::perform_pause() -> std::expected<void, ActivityError> {
    called_ = false;
    on_pause();
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    resumed_ = false;
    state_ = ActivityState::paused;
    return {};
}

auto Activity::perform_stop() -> std::expected<void, ActivityError> {
    called_ = false;
    on_stop();
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    stopped_ = true;
    state_ = ActivityState::stopped;
    return {};
}

auto Activity::perform_destroy() -> std::expected<void, ActivityError> {
    called_ = false;
    on_destroy();
    if (!called_) {
        return std::unexpected(ActivityError::super_not_called);
    }
    destroyed_ = true;
    state_ = ActivityState::destroyed;
    return {};
}

auto Activity::dispatch_activity_result(const std::string& who, int32_t request_code, int32_t result_code, const android::content::Intent& data) -> void {
    if (who.empty()) {
        on_activity_result(request_code, result_code, data);
    }
}

} // namespace android::app