// accessibility_button_interfaces.cppm
export module accessibility_button_interfaces;

import <memory>;
import <functional>;

// Forward declaration
export class AccessibilityButtonController;

export enum class service_connection_error {
    ipc_failed,
    service_not_connected,
};

// Abstract interface for a thread executor.
// This matches the one in ndk_executor.cppm.
export class IThreadExecutor {
public:
    virtual ~IThreadExecutor() = default;
    virtual void post(std::function<void()> task) = 0;
};

// Abstract interface for the AccessibilityButtonCallback.
// Clients must implement this interface.
export class AccessibilityButtonCallback {
public:
    virtual ~AccessibilityButtonCallback() = default;

    // Called when the accessibility button is clicked.
    virtual void on_clicked(AccessibilityButtonController& controller) = 0;

    // Called when the button's availability changes.
    virtual void on_availability_changed(AccessibilityButtonController& controller, bool is_available) = 0;
};

// Abstract interface for the connection to the system service.
// This will be implemented by the underlying IPC mechanism.
export class IAccessibilityServiceConnection {
public:
    virtual ~IAccessibilityServiceConnection() = default;
    
    [[nodiscard]] virtual auto is_accessibility_button_available() noexcept 
        -> std::expected<bool, service_connection_error> = 0;
};