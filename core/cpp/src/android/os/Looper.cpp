#include <android/os/Looper.h>
#include <android/os/Handler.h>
#include <poll.h>

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

    while (!looper->quitting_) {
        looper->poll_once();
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

auto Looper::add_fd(int fd, int events, fd_callback callback, void* data) -> int {
    std::lock_guard lock(mutex_);
    FdEntry entry;
    entry.fd = fd;
    entry.events = events;
    entry.callback = std::move(callback);
    entry.data = data;
    entry.cookie = next_cookie_++;
    fds_.push_back(std::move(entry));
    return fds_.back().cookie;
}

auto Looper::remove_fd(int cookie) -> int {
    std::lock_guard lock(mutex_);
    for (auto it = fds_.begin(); it != fds_.end(); ++it) {
        if (it->cookie == cookie) {
            fds_.erase(it);
            return 0;
        }
    }
    return -1;
}

void Looper::poll_once() {
    std::vector<FdEntry> local_fds;
    std::vector<struct pollfd> poll_fds;

    {
        std::unique_lock lock(mutex_);
        if (fds_.empty() && queue_.empty() && !quitting_) {
            cv_.wait_for(lock, std::chrono::milliseconds(100));
            if (fds_.empty() && queue_.empty() && !quitting_) {
                return;
            }
        }

        local_fds.reserve(fds_.size());
        poll_fds.reserve(fds_.size() + 1);
        for (const auto& fe : fds_) {
            local_fds.push_back(fe);
            struct pollfd pfd;
            pfd.fd = fe.fd;
            pfd.events = static_cast<int16_t>(fe.events);
            pfd.revents = 0;
            poll_fds.push_back(pfd);
        }
    }

    int ret = 0;
    if (!poll_fds.empty()) {
        ret = poll(poll_fds.data(), poll_fds.size(), -1);
    }

    if (ret > 0) {
        for (size_t i = 0; i < local_fds.size(); ++i) {
            if (poll_fds[i].revents != 0) {
                int result = 0;
                {
                    std::lock_guard lock(mutex_);
                    result = local_fds[i].callback(
                        local_fds[i].fd,
                        static_cast<int>(poll_fds[i].revents),
                        local_fds[i].data);
                }
                if (result > 0) {
                    return;
                }
            }
        }
    }

    QueuedMessage qm;
    {
        std::lock_guard lock(mutex_);
        if (!queue_.empty()) {
            qm = std::move(queue_.front());
            queue_.erase(queue_.begin());
        }
    }

    if (!qm.msg.callback && !qm.target) {
        return;
    }

    if (qm.msg.callback) {
        qm.msg.callback();
    } else if (qm.target) {
        qm.target->handle_message(qm.msg);
    }
}

} // namespace android::os
