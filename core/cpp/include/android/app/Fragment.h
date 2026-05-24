#pragma once

#include <android/os/Bundle.h>
#include <memory>
#include <string>
#include <optional>

namespace android::app {

class FragmentManager;
class Context;

/**
 * Fragment represents a modular section of an activity's UI/behavior.
 */
class Fragment {
public:
    enum State {
        INITIALIZING = 0,
        CREATED = 1,
        ACTIVITY_CREATED = 2,
        STOPPED = 3,
        STARTED = 4,
        RESUMED = 5
    };

    Fragment() = default;
    virtual ~Fragment() = default;

    virtual void on_attach(std::shared_ptr<Context> context) { called_ = true; }
    virtual void on_create(const android::os::Bundle& saved_instance_state) { called_ = true; }
    virtual void on_start() { called_ = true; }
    virtual void on_resume() { called_ = true; }
    virtual void on_pause() { called_ = true; }
    virtual void on_stop() { called_ = true; }
    virtual void on_destroy() { called_ = true; }
    virtual void on_detach() { called_ = true; }

    [[nodiscard]] auto get_state() const noexcept -> State { return state_; }
    [[nodiscard]] auto get_tag() const -> const std::optional<std::string>& { return tag_; }
    auto set_tag(const std::string& tag) -> void { tag_ = tag; }

private:
    State state_{INITIALIZING};
    bool called_{false};
    std::optional<std::string> tag_;
    std::shared_ptr<FragmentManager> child_fragment_manager_;
};

} // namespace android::app
