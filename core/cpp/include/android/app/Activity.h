#pragma once

#include <android/view/ContextThemeWrapper.h>
#include <android/view/Window.h>
#include <android/view/WindowManager.h>
#include <android/os/Bundle.h>
#include <android/os/IBinder.h>
#include <android/content/Intent.h>
#include <android/content/res/Configuration.h>
#include <memory>
#include <expected>
#include <android/app/ActivityCommon.h>

namespace android::app {

enum class ActivityState {
    initialized,
    created,
    started,
    resumed,
    paused,
    stopped,
    destroyed
};

class Activity : public android::view::ContextThemeWrapper {
public:
    Activity() : android::view::ContextThemeWrapper(nullptr) {}
    explicit Activity(std::shared_ptr<android::content::Context> base) : android::view::ContextThemeWrapper(std::move(base)) {}
    virtual ~Activity() = default;

    Activity(const Activity&) = delete;
    Activity& operator=(const Activity&) = delete;
    Activity(Activity&&) = delete;
    Activity& operator=(Activity&&) = delete;

protected:
    virtual auto on_create(const android::os::Bundle& saved_instance_state) -> void;
    virtual auto on_start() -> void;
    virtual auto on_restart() -> void;
    virtual auto on_resume() -> void;
    virtual auto on_pause() -> void;
    virtual auto on_stop() -> void;
    virtual auto on_destroy() -> void;
    virtual auto on_save_instance_state(android::os::Bundle& out_state) -> void {}
    virtual auto on_activity_result(int32_t request_code, int32_t result_code, const std::optional<android::content::Intent>& data) -> void {}

public:
    // API
    auto set_content_view(int layout_res_id) -> void;
    auto finish() -> void;
    [[nodiscard]] auto get_state() const noexcept -> ActivityState { return state_; }

    [[nodiscard]] auto get_intent() const -> std::shared_ptr<android::content::Intent> { return intent_; }
    auto set_intent(std::shared_ptr<android::content::Intent> intent) -> void { intent_ = std::move(intent); }

    auto start_activity_for_result(const android::content::Intent& intent, int32_t request_code, std::optional<android::os::Bundle> options = std::nullopt) -> void;
    auto set_result(int32_t result_code, std::optional<android::content::Intent> data = std::nullopt) -> void;

    // System Hooks
    virtual auto on_configuration_changed(const android::content::res::Configuration& new_config) -> void;
    virtual auto on_low_memory() -> void;
    virtual auto on_trim_memory(int32_t level) -> void;

    // UI & Window
    [[nodiscard]] auto get_window() const -> std::shared_ptr<android::view::Window> { return window_; }
    [[nodiscard]] auto get_window_manager() const -> std::shared_ptr<android::view::WindowManager> { return window_manager_; }

    // Internal State Management (Called by ActivityThread)
    auto perform_create(const android::os::Bundle& icicle) -> std::expected<void, ActivityError>;
    auto perform_start() -> std::expected<void, ActivityError>;
    auto perform_restart() -> std::expected<void, ActivityError>;
    auto perform_resume() -> std::expected<void, ActivityError>;
    auto perform_pause() -> std::expected<void, ActivityError>;
    auto perform_stop() -> std::expected<void, ActivityError>;
    auto perform_destroy() -> std::expected<void, ActivityError>;

    auto dispatch_activity_result(const std::string& who, int32_t request_code, int32_t result_code, const android::content::Intent& data) -> void;

    [[nodiscard]] auto get_token() const -> std::shared_ptr<android::os::IBinder> { return token_; }
    auto set_token(std::shared_ptr<android::os::IBinder> token) -> void { token_ = std::move(token); }

protected:
    std::shared_ptr<android::view::Window> window_;
    std::shared_ptr<android::view::WindowManager> window_manager_;
    int32_t result_code_{0}; // RESULT_CANCELED
    std::optional<android::content::Intent> result_data_;

private:
    ActivityState state_{ActivityState::initialized};
    std::shared_ptr<android::content::Intent> intent_;
    std::shared_ptr<android::os::IBinder> token_;

    bool called_{false};
    bool resumed_{false};
    bool stopped_{false};
    bool destroyed_{false};
};

} // namespace android::app
