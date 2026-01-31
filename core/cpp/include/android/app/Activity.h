#pragma once

#include <android/view/ContextThemeWrapper.h>
#include <android/os/Bundle.h>
#include <android/os/IBinder.h>
#include <android/content/Intent.h>
#include <memory>

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
    virtual auto on_create(const android::os::Bundle& saved_instance_state) -> void {}
    virtual auto on_start() -> void {}
    virtual auto on_resume() -> void {}
    virtual auto on_pause() -> void {}
    virtual auto on_stop() -> void {}
    virtual auto on_destroy() -> void {}
    virtual auto on_save_instance_state(android::os::Bundle& out_state) -> void {}

public:
    auto set_content_view(int layout_res_id) -> void;
    auto finish() -> void;
    [[nodiscard]] auto get_state() const noexcept -> ActivityState { return state_; }

    [[nodiscard]] auto get_intent() const -> std::shared_ptr<android::content::Intent> { return intent_; }
    auto set_intent(std::shared_ptr<android::content::Intent> intent) -> void { intent_ = std::move(intent); }

    auto perform_create(const android::os::Bundle& icicle) -> void;
    auto perform_start() -> void;
    auto perform_resume() -> void;
    auto perform_pause() -> void;
    auto perform_stop() -> void;
    auto perform_destroy() -> void;

    [[nodiscard]] auto get_token() const -> std::shared_ptr<android::os::IBinder> { return token_; }
    auto set_token(std::shared_ptr<android::os::IBinder> token) -> void { token_ = std::move(token); }

private:
    ActivityState state_{ActivityState::initialized};
    std::shared_ptr<android::content::Intent> intent_;
    std::shared_ptr<android::os::IBinder> token_;
};

} // namespace android::app
