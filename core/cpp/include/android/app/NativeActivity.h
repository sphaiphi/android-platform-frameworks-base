#pragma once

#include <android/app/Activity.h>

namespace android::app {

/**
 * Convenience for implementing an activity that will be implemented
 * purely in native code.
 */
class NativeActivity : public Activity {
public:
    NativeActivity();
    virtual ~NativeActivity() = default;

    [[nodiscard]] auto get_native_handle() const noexcept -> long { return native_handle_; }

    virtual void on_window_focus_changed(bool has_focus);

protected:
    auto on_create(const android::os::Bundle& saved_instance_state) -> void override;
    auto on_start() -> void override;
    auto on_resume() -> void override;
    auto on_pause() -> void override;
    auto on_stop() -> void override;
    auto on_destroy() -> void override;

    auto on_configuration_changed(const android::content::res::Configuration& new_config) -> void override;
    auto on_low_memory() -> void override;

private:
    long native_handle_{0};
};

} // namespace android::app
