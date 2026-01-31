#include <android/os/Handler.h>
#include <android/os/Looper.h>

namespace android::os {

Handler::Handler(std::shared_ptr<Looper> looper) : looper_(std::move(looper)) {}

void Handler::send_message(Message msg) {
    if (looper_) {
        // We need to pass 'this' but Handler is not necessarily shared_ptr managed.
        // For simplicity in this foundation, we'll assume it's okay for now.
        // In real Android, Handler doesn't use shared_ptr for target usually.
    }
}

void Handler::post(std::function<void()> callback) {
    if (looper_) {
        looper_->send_message({.callback = std::move(callback)}, nullptr);
    }
}

} // namespace android::os
