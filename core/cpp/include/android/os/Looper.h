#pragma once

#include <android/os/Message.h>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace android::os {

class Handler;

/**
 * Class used to run a message loop for a thread.
 * 
 * Threads by default do not have a message loop associated with them.
 * To create one, call prepare() in the thread that is to run the loop, 
 * and then loop() to have it process messages until the loop is stopped.
 */
class Looper : public std::enable_shared_from_this<Looper> {
public:
    /**
     * Initialize the current thread as a looper.
     */
    static void prepare();

    /**
     * Initialize the current thread as a looper and mark it as the main looper.
     */
    static void prepare_main_looper();

    /**
     * Return the Looper object associated with the current thread.
     */
    static auto my_looper() -> std::shared_ptr<Looper>;

    /**
     * Returns the application's main looper.
     */
    static auto get_main_looper() -> std::shared_ptr<Looper>;

    /**
     * Run the message queue in this thread.
     */
    static void loop();

    /**
     * Quits the looper.
     */
    void quit();

    /**
     * Send a message to be processed by this looper.
     */
    void send_message(const Message& msg, std::shared_ptr<Handler> target);

    /**
     * Callback invoked when an FD becomes ready.
     * Returns 1 if the event was consumed, 0 otherwise.
     */
    using fd_callback = std::function<int(int fd, int events, void* data)>;

    /**
     * Register a file descriptor callback with the Looper.
     */
    auto add_fd(int fd, int events, fd_callback callback, void* data = nullptr) -> int;

    /**
     * Unregister a previously registered file descriptor.
     */
    auto remove_fd(int cookie) -> int;

    /**
     * Poll once, processing any ready FDs and one message.
     */
    void poll_once();

private:
    struct FdEntry {
        int fd{-1};
        int events{0};
        fd_callback callback;
        void* data{nullptr};
        int cookie{0};
    };

    struct QueuedMessage {
        Message msg;
        std::shared_ptr<Handler> target;
    };

    std::vector<QueuedMessage> queue_;
    std::vector<FdEntry> fds_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool quitting_{false};
    int next_cookie_{1};

    static thread_local std::shared_ptr<Looper> s_thread_local_looper;
    static std::shared_ptr<Looper> s_main_looper;
};

} // namespace android::os
