// accessibility_button_controller.cppm
export module accessibility_button_controller;

import accessibility_button_interfaces;
import <memory>;
import <expected>;
import <mutex>;
import <map>;
import <utility>; // For std::move

export class AccessibilityButtonController final 
    : public std::enable_shared_from_this<AccessibilityButtonController> {

public:
    // Factory function to ensure proper shared_ptr management
    [[nodiscard]] static auto create(
        std::shared_ptr<IAccessibilityServiceConnection> connection
    ) -> std::shared_ptr<AccessibilityButtonController> {
        // Use a private constructor, accessible via a helper struct,
        // to enforce creation via std::make_shared.
        struct MakeSharedEnabler : public AccessibilityButtonController {
            MakeSharedEnabler(std::shared_ptr<IAccessibilityServiceConnection> conn)
                : AccessibilityButtonController(std::move(conn)) {}
        };
        return std::make_shared<MakeSharedEnabler>(std::move(connection));
    }

    AccessibilityButtonController(const AccessibilityButtonController&) = delete;
    auto operator=(const AccessibilityButtonController&) -> AccessibilityButtonController& = delete;
    AccessibilityButtonController(AccessibilityButtonController&&) = delete;
    auto operator=(AccessibilityButtonController&&) -> AccessibilityButtonController& = delete;

    // Queries the system for the accessibility button's availability.
    [[nodiscard]] auto is_accessibility_button_available() noexcept -> bool {
        if (auto result = connection_->is_accessibility_button_available(); result.has_value()) {
            return result.value();
        }
        // On error, return false as per the original Java implementation's contract.
        return false;
    }
    
    // Registers a callback for accessibility button events.
    void register_callback(
        std::shared_ptr<AccessibilityButtonCallback> callback,
        std::shared_ptr<IThreadExecutor> executor
    ) {
        if (!callback || !executor) {
            // Or throw std::invalid_argument, depending on desired contract.
            return; 
        }
        std::lock_guard lock(mutex_);
        callbacks_[callback.get()] = {std::weak_ptr(callback), std::move(executor)};
    }

    // Unregisters a callback.
    void unregister_callback(const std::shared_ptr<AccessibilityButtonCallback>& callback) {
        if (!callback) return;
        std::lock_guard lock(mutex_);
        callbacks_.erase(callback.get());
    }

    // --- Dispatch methods (called by the service connection) ---

    // Dispatches a click event to all registered callbacks.
    void dispatch_clicked() {
        auto callbacks_copy = get_callbacks_copy();
        auto self = shared_from_this();

        for (const auto& [callback_ptr, executor] : callbacks_copy) {
            executor->post([self, callback_ptr]() {
                if (auto cb = callback_ptr.lock()) { // Check if callback object still exists
                    cb->on_clicked(*self);
                }
            });
        }
    }

    // Dispatches an availability change event.
    void dispatch_availability_changed(bool is_available) {
        auto callbacks_copy = get_callbacks_copy();
        auto self = shared_from_this();

        for (const auto& [callback_ptr, executor] : callbacks_copy) {
            executor->post([self, callback_ptr, is_available]() {
                if (auto cb = callback_ptr.lock()) {
                    cb->on_availability_changed(*self, is_available);
                }
            });
        }
    }

private:
    // Private constructor to force use of the `create` factory.
    explicit AccessibilityButtonController(
        std::shared_ptr<IAccessibilityServiceConnection> connection
    ) : connection_{std::move(connection)} {}

    // Helper struct to hold a weak_ptr to the callback and a shared_ptr to the executor.
    struct CallbackEntry {
        std::weak_ptr<AccessibilityButtonCallback> callback;
        std::shared_ptr<IThreadExecutor> executor;
    };

    // Safely creates a copy of the callback map to prevent deadlocks during dispatch.
    [[nodiscard]] auto get_callbacks_copy() -> std::map<AccessibilityButtonCallback*, std::shared_ptr<IThreadExecutor>> {
        std::map<AccessibilityButtonCallback*, std::shared_ptr<IThreadExecutor>> copy;
        std::lock_guard lock(mutex_);
        for (auto it = callbacks_.begin(); it != callbacks_.end(); ) {
            if (it->second.callback.expired()) {
                // Clean up expired weak_ptrs during the copy
                it = callbacks_.erase(it);
            } else {
                copy.emplace(it->first, it->second.executor);
                ++it;
            }
        }
        return copy;
    }

    std::shared_ptr<IAccessibilityServiceConnection> connection_;
    std::mutex mutex_{};
    // Map from raw pointer (for quick lookup) to the callback entry
    std::map<AccessibilityButtonCallback*, CallbackEntry> callbacks_{};
};