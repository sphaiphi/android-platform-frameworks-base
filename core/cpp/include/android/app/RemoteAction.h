#pragma once

#include <string>
#include <memory>

namespace android::app {

// Forward declarations for types not yet implemented in C++
class PendingIntent;

/**
 * Represents an actionable item that can be triggered from another process.
 */
class RemoteAction {
public:
    RemoteAction(const std::string& title, const std::string& contentDescription, std::shared_ptr<PendingIntent> actionIntent)
        : title_(title), content_description_(contentDescription), action_intent_(std::move(actionIntent)), enabled_(true), should_show_icon_(true) {}

    [[nodiscard]] auto get_title() const -> const std::string& { return title_; }
    [[nodiscard]] auto get_content_description() const -> const std::string& { return content_description_; }
    [[nodiscard]] auto get_action_intent() const -> std::shared_ptr<PendingIntent> { return action_intent_; }

    auto set_enabled(bool enabled) -> void { enabled_ = enabled; }
    [[nodiscard]] auto is_enabled() const noexcept -> bool { return enabled_; }

    auto set_should_show_icon(bool should_show) -> void { should_show_icon_ = should_show; }
    [[nodiscard]] auto should_show_icon() const noexcept -> bool { return should_show_icon_; }

private:
    // Icon icon_; // TBD: Implement Icon class
    std::string title_;
    std::string content_description_;
    std::shared_ptr<PendingIntent> action_intent_;
    bool enabled_;
    bool should_show_icon_;
};

} // namespace android::app
