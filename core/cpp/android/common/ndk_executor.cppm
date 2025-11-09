// ndk_executor.cppm

// Global module fragment for non-modular C headers
module;
#include <android/looper.h>
#include <fcntl.h>
#include <unistd.h>

export module ndk_executor;

import std.core;
import std.threading;
import <memory>; // For shared_ptr and enable_shared_from_this
import <queue>;

export namespace ndk {

/**
 * @brief Abstract interface for a thread executor that can post tasks.
 */
class IThreadExecutor {
public:
    virtual ~IThreadExecutor() = default;
    
    /**
     * @brief Posts a task to be executed by the executor's thread.
     * @param task The function to execute.
     */
    virtual void post(std::function<void()> task) = 0;
};

/**
 * @brief A concrete IThreadExecutor implementation using Android's NDK ALooper.
 *
 * This executor runs a dedicated thread with an ALooper event loop, allowing
 * tasks to be posted and executed sequentially on that thread.
 */
class NdkThreadExecutor final : public IThreadExecutor, public std::enable_shared_from_this<NdkThreadExecutor> {
public:
    /**
     * @brief Creates and starts a new NdkThreadExecutor.
     * @return A shared_ptr to the newly created executor.
     * @throws std::runtime_error if thread or looper initialization fails.
     */
    [[nodiscard]] static auto create() -> std::shared_ptr<NdkThreadExecutor> {
        // Use a private constructor with a factory to safely manage the object's
        // lifetime with its own thread via the enable_shared_from_this pattern.
        struct MakeSharedEnabler : public NdkThreadExecutor {};
        auto executor = std::make_shared<MakeSharedEnabler>();
        executor->start();
        return executor;
    }

    NdkThreadExecutor(const NdkThreadExecutor&) = delete;
    auto operator=(const NdkThreadExecutor&) -> NdkThreadExecutor& = delete;
    NdkThreadExecutor(NdkThreadExecutor&&) = delete;
    auto operator=(NdkThreadExecutor&&) -> NdkThreadExecutor& = delete;

    ~NdkThreadExecutor() final {
        if (m_thread_.joinable()) {
            m_is_running_ = false;
            if (m_looper_ != nullptr) {
                ALooper_wake(m_looper_);
            }
            m_thread_.join();
        }
        if (m_looper_ != nullptr) {
            ALooper_removeFd(m_looper_, m_pipe_fd_[0]);
            ALooper_release(m_looper_);
        }
        if (m_pipe_fd_[0] != -1) close(m_pipe_fd_[0]);
        if (m_pipe_fd_[1] != -1) close(m_pipe_fd_[1]);
    }

    void post(std::function<void()> task) final {
        {
            std::lock_guard lock(m_mutex_);
            m_task_queue_.push(std::move(task));
        }
        // Wake the looper to process the new task.
        if (write(m_pipe_fd_[1], "W", 1) != 1) {
            throw std::runtime_error("Failed to write to executor pipe");
        }
    }

private:
    explicit NdkThreadExecutor() = default;

    void start() {
        if (pipe(m_pipe_fd_) == -1) {
            throw std::runtime_error("Failed to create pipe for NdkThreadExecutor");
        }
        m_thread_ = std::thread(&NdkThreadExecutor::run, this);
    }

    void run() {
        m_looper_ = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
        if (m_looper_ == nullptr) {
            // A real library might use a promise to signal failure to the creating thread.
            // For now, we assume it won't fail or log an error.
            return;
        }
        
        static ALooper_callbackFunc looper_callback_ptr = &looper_callback;
        if (ALooper_addFd(m_looper_, m_pipe_fd_[0], ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, looper_callback_ptr, this) != 1) {
             return;
        }

        m_is_running_ = true;
        while (m_is_running_) {
            ALooper_pollAll(-1, nullptr, nullptr, nullptr);
        }
    }
    
    void process_tasks() {
        char buffer[16]; // Drain the pipe to prevent multiple triggers for one wake.
        while (read(m_pipe_fd_[0], buffer, sizeof(buffer)) > 0) {}

        std::queue<std::function<void()>> local_queue;
        {
            std::lock_guard lock(m_mutex_);
            if(m_task_queue_.empty()) return;
            local_queue.swap(m_task_queue_);
        }
        while (!local_queue.empty()) {
            auto task = std::move(local_queue.front());
            local_queue.pop();
            if (task) {
                task();
            }
        }
    }

    // Static C-style callback required by the ALooper C API.
    static auto looper_callback(int /*fd*/, int /*events*/, void* data) -> int {
        auto* self = static_cast<NdkThreadExecutor*>(data);
        if (self->m_is_running_) {
            self->process_tasks();
        }
        return 1; // Continue receiving callbacks.
    }

    std::thread m_thread_{};
    ALooper* m_looper_{nullptr};
    int m_pipe_fd_[2]{-1, -1};
    std::mutex m_mutex_{};
    std::queue<std::function<void()>> m_task_queue_{};
    std::atomic<bool> m_is_running_{false};
};

} // namespace ndk