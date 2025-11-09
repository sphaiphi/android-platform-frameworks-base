export module accessibility.controller;

import accessibility.interfaces;
import <map>;
import <mutex>;
import <iostream>;
import <utility>;
import <memory>;
import <stdexcept>;

namespace android {
namespace accessibility {
/**
 * @brief C++ implementation of AccessibilityButtonController.
 * This class is final and thread-safe. It acts as a client-side proxy
 * for interacting with the system's accessibility button.
 */
export class AccessibilityButtonController final : public std::enable_shared_from_this<AccessibilityButtonController> {
public:

    /**
     * @brief Constructs the controller.
     * @param connection A shared pointer to an IPC connection interface. Must not be null.
     */
    explicit AccessibilityButtonController(std::shared_ptr<IAccessibilityServiceConnection> connection)
        : m_connection_{std::move(connection)} {
        if (!m_connection_) {
            throw std::invalid_argument("IAccessibilityServiceConnection must not be null");
        }
    }

    /**
     * @brief Synchronously queries if the accessibility button is available.
     * @return true if available, false otherwise or on IPC failure.
     */
    [[nodiscard]] auto is_accessibility_button_available() const -> bool {
        const std::optional<bool> result = m_connection_->is_accessibility_button_available();
        if (!result) {
            std::cerr << "Warning: IPC failed while checking button availability." << std::endl;
            return false;
        }
        return *result;
    }

    /**
     * @brief Registers a callback to receive accessibility button events.
     * @param callback The callback instance to register. Must not be null.
     * @param executor The executor to run the callback on. Must not be null.
     * @note The caller retains ownership of the callback object and is responsible
     *       for unregistering it before its destruction.
     */
    void register_callback(AccessibilityButtonCallback* callback, std::shared_ptr<IThreadExecutor> executor) {
        if (callback == nullptr || executor == nullptr) {
            throw std::invalid_argument("Callback and executor must not be null");
        }
        std::lock_guard lock(m_mutex_);
        m_callbacks_[callback] = std::move(executor);
    }

    /**
     * @brief Unregisters a previously registered callback.
     * @param callback The callback instance to unregister. Must not be null.
     * It is safe to call this with a callback that was not registered.
     */
    void unregister_callback(AccessibilityButtonCallback* callback) {
        if (callback == nullptr) {
            throw std::invalid_argument("Callback must not be null");
        }
        std::lock_guard lock(m_mutex_);
        m_callbacks_.erase(callback);
    }
    
    // --- Dispatch Methods ---
    // These would typically be called by the IPC layer. They are public here for demonstration.

    void dispatch_clicked() {
        // The copy-on-dispatch pattern is critical for re-entrant safety.
        auto callbacks_copy = get_callbacks_copy();
        for (const auto& [callback, executor] : callbacks_copy) {
            auto self = shared_from_this(); // Ensure controller is alive for the async call.
            executor->post([callback, self]() {
                callback->on_clicked(self.get());
            });
        }
    }
    
    void dispatch_availability_changed(bool is_available) {
        auto callbacks_copy = get_callbacks_copy();
        for (const auto& [callback, executor] : callbacks_copy) {
            auto self = shared_from_this();
            executor->post([callback, self, is_available]() {
                callback->on_availability_changed(self.get(), is_available);
            });
        }
    }

private:
    using CallbackMap = std::map<AccessibilityButtonCallback*, std::shared_ptr<IThreadExecutor>>;
    
    // Helper to safely get a copy of the callbacks map.
    [[nodcard]] auto get_callbacks_copy() -> CallbackMap {
        std::lock_guard lock(m_mutex_);
        return m_callbacks_.empty() ? CallbackMap{} : m_callbacks_; // Return a copy
    }

    std::shared_ptr<IAccessibilityServiceConnection> m_connection_;
    std::mutex m_mutex_{};
    CallbackMap m_callbacks_{};
};
} // namespace accessibility
} // namespace android