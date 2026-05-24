#pragma once

#include <android/os/Message.h>
#include <memory>

namespace android::os {

class Looper;

/**
 * A Handler allows you to send and process Message and Runnable objects associated with a thread's MessageQueue.
 */
class Handler {
public:
    explicit Handler(std::shared_ptr<Looper> looper);
    virtual ~Handler() = default;

    /**
     * Subclasses must implement this to receive messages.
     */
    virtual void handle_message(const Message& msg) {}
    
    /**
     * Pushes a message onto the end of the message queue.
     */
    void send_message(Message msg);

    /**
     * Causes the Runnable r to be added to the message queue.
     */
    void post(std::function<void()> callback);

    /**
     * Returns the looper associated with this handler.
     */
    auto get_looper() const -> std::shared_ptr<Looper> { return looper_; }

private:
    std::shared_ptr<Looper> looper_;
};

} // namespace android::os
