// accessibilityservice-button_controller.cppm
export module accessibilityservice:button_controller;

import :internal;
import ndk_executor;

import <memory>;
import <functional>;
import <map>;
import <mutex>;
import <stdexcept>;

export namespace accessibility {

// Forward declaration
class IAccessibilityButtonController;

/**
 * @class IAccessibilityButtonCallback
 * @brief Interface for receiving callbacks about the accessibility button.
 */
class IAccessibilityButtonCallback {
public:
    virtual ~IAccessibilityButtonCallback() = default;
    virtual void on_clicked(IAccessibilityButtonController* controller) = 0;
    virtual void on_availability_changed(IAccessibilityButtonController* controller, bool available) = 0;
};

/**
 * @class IAccessibilityButtonController
 * @brief Interface for interacting with the system accessibility button.
 */
class IAccessibilityButtonController {
public:
    virtual ~IAccessibilityButtonController() = default;

    [[nodiscard]] virtual auto is_accessibility_button_available() const -> bool = 0;

    virtual void register_accessibility_button_callback(
        IAccessibilityButtonCallback* callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) = 0;

    virtual void unregister_accessibility_button_callback(IAccessibilityButtonCallback* callback) = 0;
};

/**
 * @brief Factory function to create an instance of the controller.
 */
auto create_accessibility_button_controller(
    std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
    -> std::unique_ptr<IAccessibilityButtonController>;

} // namespace accessibility

// --- Implementation ---

namespace accessibility {

class AccessibilityButtonControllerImpl final : public IAccessibilityButtonController {
public:
    explicit AccessibilityButtonControllerImpl(
        std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
        : service_connection_{std::move(connection)} {
        if (!service_connection_) {
            throw std::invalid_argument("Service connection cannot be null.");
        }
    }

    [[nodiscard]] auto is_accessibility_button_available() const -> bool override {
        auto result = service_connection_->is_accessibility_button_available();
        if (!result) return false;
        return *result;
    }

    void register_accessibility_button_callback(
        IAccessibilityButtonCallback* callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) override {
        if (!callback || !executor) return;
        std::lock_guard lock(callbacks_mutex_);
        callbacks_.emplace(callback, std::move(executor));
    }

    void unregister_accessibility_button_callback(IAccessibilityButtonCallback* callback) override {
        if (!callback) return;
        std::lock_guard lock(callbacks_mutex_);
        callbacks_.erase(callback);
    }
    
    // Internal dispatch methods
    void dispatch_clicked() {
        auto callbacks_copy = get_callbacks_copy();
        for (const auto& [callback, executor] : callbacks_copy) {
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

    [[nodiscard]] auto get_callbacks_copy() -> CallbackMap {
        std::lock_guard lock(callbacks_mutex_);
        return callbacks_;
    }

    std::shared_ptr<internal::IAccessibilityServiceConnection> service_connection_;
    std::mutex callbacks_mutex_{};
    CallbackMap callbacks_{};
};

auto create_accessibility_button_controller(
    std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
    -> std::unique_ptr<IAccessibilityButtonController> {
    return std::make_unique<AccessibilityButtonControllerImpl>(std::move(connection));
}

} // namespace accessibility