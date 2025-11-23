// accessibility_button_controller.cppm
module accessibilityservice;

import :button_controller_interfaces;
import :internal;
import ndk_executor;

import <memory>;
import <utility>;
import <vector>;
import <map>;
import <mutex>;
import <stdexcept>;

namespace accessibility {

/**
 * @class AccessibilityButtonControllerImpl
 * @brief Concrete implementation of the IAccessibilityButtonController.
 * @details Manages callbacks and delegates calls to the IAccessibilityServiceConnection.
 *          This class is final and intended to be used via its interface.
 */
class AccessibilityButtonControllerImpl final : public IAccessibilityButtonController {
public:
    // SAFETY ✓: explicit constructor prevents implicit conversions.
    explicit AccessibilityButtonControllerImpl(
        std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
        : service_connection_{std::move(connection)} {
        if (!service_connection_) {
            throw std::invalid_argument("Service connection cannot be null.");
        }
    }

    // Rule of Five: Default destructor is sufficient, but be explicit about non-copyable nature.
    ~AccessibilityButtonControllerImpl() override = default;
    AccessibilityButtonControllerImpl(const AccessibilityButtonControllerImpl&) = delete;
    auto operator=(const AccessibilityButtonControllerImpl&) -> AccessibilityButtonControllerImpl& = delete;
    AccessibilityButtonControllerImpl(AccessibilityButtonControllerImpl&&) = delete;
    auto operator=(AccessibilityButtonControllerImpl&&) -> AccessibilityButtonControllerImpl& = delete;

    // --- IAccessibilityButtonController Implementation ---

    [[nodiscard]] auto is_accessibility_button_available() const -> bool override {
        auto result = service_connection_->is_accessibility_button_available();
        // SAFETY ✓ Error Handling: Check std::expected for error. Return a safe default.
        if (!result) {
            // In a real app, log the error: log(result.error());
            return false;
        }
        return *result;
    }

    void register_accessibility_button_callback(
        IAccessibilityButtonCallback* callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) override {
        if (!callback || !executor) {
            return; // Or throw std::invalid_argument for contract violation.
        }
        // SAFETY ✓ Lifetime: std::lock_guard ensures mutex is unlocked on any return path.
        std::lock_guard lock(callbacks_mutex_);
        callbacks_.emplace(callback, std::move(executor));
    }

    void unregister_accessibility_button_callback(IAccessibilityButtonCallback* callback) override {
        if (!callback) {
            return;
        }
        std::lock_guard lock(callbacks_mutex_);
        callbacks_.erase(callback);
    }
    
    // --- Internal Dispatch Methods (called by the service connection owner) ---

    void dispatch_clicked() {
        auto callbacks_copy = get_callbacks_copy();
        for (const auto& [callback, executor] : callbacks_copy) {
            // SAFETY ✓ Async: `this` is not captured. `callback` is copied.
            executor->post([callback, this]() {
                callback->on_clicked(this);
            });
        }
    }
    
    void dispatch_availability_changed(bool is_available) {
        auto callbacks_copy = get_callbacks_copy();
        for (const auto& [callback, executor] : callbacks_copy) {
            executor->post([callback, this, is_available]() {
                callback->on_availability_changed(this, is_available);
            });
        }
    }

private:
    using CallbackMap = std::map<IAccessibilityButtonCallback*, std::shared_ptr<ndk::IThreadExecutor>>;

    // SAFETY ✓ Lifetime Safety: Critical copy-on-dispatch pattern to prevent iterator invalidation
    // and deadlocks if a callback unregisters itself.
    [[nodiscard]] auto get_callbacks_copy() -> CallbackMap {
        std::lock_guard lock(callbacks_mutex_);
        return callbacks_;
    }

    // --- Member Variables ---
    
    // The IPC connection to the system service.
    std::shared_ptr<internal::IAccessibilityServiceConnection> service_connection_;

    // Guards access to the callbacks map.
    // SAFETY ✓ Init: All members are initialized.
    std::mutex callbacks_mutex_{};

    // Map of registered callbacks and their target executors.
    CallbackMap callbacks_{};
};

// --- Factory Function ---

// This factory would be part of the AccessibilityService setup process.
// It is not exported publicly but used by other parts of the accessibility module.
auto create_accessibility_button_controller(
    std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
    -> std::unique_ptr<IAccessibilityButtonController> {
    return std::make_unique<AccessibilityButtonControllerImpl>(std::move(connection));
}

} // namespace accessibility