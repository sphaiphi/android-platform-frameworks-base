#include <android/app/Notification.h>

namespace android::app {

Notification::Notification() = default;

Notification::Builder::Builder(std::shared_ptr<Context> /*context*/, const std::string& channelId) {
    notification_ = std::make_shared<Notification>();
    notification_->channel_id_ = channelId;
}

Notification::Builder& Notification::Builder::set_content_title(const std::string& title) {
    notification_->content_title_ = title;
    return *this;
}

Notification::Builder& Notification::Builder::set_content_text(const std::string& text) {
    notification_->content_text_ = text;
    return *this;
}

Notification::Builder& Notification::Builder::set_small_icon(int icon) {
    notification_->small_icon_ = icon;
    return *this;
}

auto Notification::Builder::build() -> std::shared_ptr<Notification> {
    return notification_;
}

} // namespace android::app
