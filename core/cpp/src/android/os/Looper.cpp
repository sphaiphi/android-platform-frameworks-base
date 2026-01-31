#include <android/os/Looper.h>
#include <android/os/Handler.h>

namespace android::os {

thread_local std::shared_ptr<Looper> Looper::s_thread_local_looper = nullptr;
std::shared_ptr<Looper> Looper::s_main_looper = nullptr;

void Looper::prepare() {
    if (s_thread_local_looper == nullptr) {
        s_thread_local_looper = std::make_shared<Looper>();
    }
}

void Looper::prepare_main_looper() {
    prepare();
    s_main_looper = my_looper();
}

auto Looper::my_looper() -> std::shared_ptr<Looper> {
    return s_thread_local_looper;
}

auto Looper::get_main_looper() -> std::shared_ptr<Looper> {
    return s_main_looper;
}

void Looper::loop() {
    auto looper = my_looper();
    if (looper == nullptr) {
        return;
    }

    while (true) {
        QueuedMessage qm;
        {
            std::unique_lock lock(looper->mutex_);
            looper->cv_.wait(lock, [looper] { return looper->quitting_ || !looper->queue_.empty(); });
            if (looper->quitting_ && looper->queue_.empty()) {
                return;
            }
            qm = std::move(looper->queue_.front());
            looper->queue_.erase(looper->queue_.begin());
        }

        if (qm.msg.callback) {
            qm.msg.callback();
        } else if (qm.target) {
            qm.target->handle_message(qm.msg);
        }
    }
}

void Looper::quit() {
    std::lock_guard lock(mutex_);
    quitting_ = true;
    cv_.notify_all();
}

void Looper::send_message(const Message& msg, std::shared_ptr<Handler> target) {
    std::lock_guard lock(mutex_);
    queue_.push_back({msg, target});
    cv_.notify_one();
}

} // namespace android::os
