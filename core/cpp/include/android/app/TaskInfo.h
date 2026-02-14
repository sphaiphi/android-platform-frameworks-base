#pragma once

#include <android/app/WindowConfiguration.h>
#include <android/content/Intent.h>
#include <android/content/ComponentName.h>
#include <memory>
#include <string>

namespace android::app {

/**
 * Data container used to store and communicate information about a particular task.
 */
class TaskInfo {
public:
    TaskInfo() = default;

    auto get_task_id() const noexcept -> int { return task_id_; }
    auto set_task_id(int id) -> void { task_id_ = id; }

    auto is_visible() const noexcept -> bool { return is_visible_; }
    auto set_visible(bool visible) -> void { is_visible_ = visible; }

    auto get_window_configuration() const -> const WindowConfiguration& { return window_configuration_; }
    auto get_window_configuration_mutable() -> WindowConfiguration& { return window_configuration_; }

    auto get_base_intent() const -> std::shared_ptr<android::content::Intent> { return base_intent_; }
    auto set_base_intent(std::shared_ptr<android::content::Intent> intent) -> void { base_intent_ = std::move(intent); }

    auto get_top_activity() const -> const android::content::ComponentName& { return top_activity_; }
    auto set_top_activity(const android::content::ComponentName& top) -> void { top_activity_ = top; }

private:
    int task_id_{0};
    bool is_visible_{false};
    WindowConfiguration window_configuration_;
    std::shared_ptr<android::content::Intent> base_intent_;
    android::content::ComponentName top_activity_;
};

} // namespace android::app
