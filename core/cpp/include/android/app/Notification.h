#pragma once

#include <string>
#include <memory>
#include <vector>
#include <android/os/Bundle.h>

namespace android::app {

class Context;

/**
 * A persistent message or event presented to the user.
 */
class Notification {
public:
    Notification();
    virtual ~Notification() = default;

    class Builder {
    public:
        Builder(std::shared_ptr<Context> context, const std::string& channelId);
        
        Builder& set_content_title(const std::string& title);
        Builder& set_content_text(const std::string& text);
        Builder& set_small_icon(int icon);
        
        auto build() -> std::shared_ptr<Notification>;

    private:
        std::shared_ptr<Notification> notification_;
    };

    [[nodiscard]] auto get_channel_id() const -> const std::string& { return channel_id_; }

private:
    std::string channel_id_;
    std::string content_title_;
    std::string content_text_;
    int small_icon_{0};
    android::os::Bundle extras_;
};

} // namespace android::app
