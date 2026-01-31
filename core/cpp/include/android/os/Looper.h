#pragma once

#include <android/os/Message.h>
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

private:
    struct QueuedMessage {
        Message msg;
        std::shared_ptr<Handler> target;
    };

    std::vector<QueuedMessage> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool quitting_{false};

    static thread_local std::shared_ptr<Looper> s_thread_local_looper;
    static std::shared_ptr<Looper> s_main_looper;
};

} // namespace android::os
