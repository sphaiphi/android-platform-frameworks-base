// accessibilityservice.cppm
export module accessibilityservice;

import :types;
import <memory>;
import <functional>;

// Re-export the necessary public interfaces for clients.
export import :button_controller_interfaces;
export import ndk_executor; // Export the executor interface for users

export namespace accessibility {

// Forward-declare the implementation detail PIMPL class
class AccessibilityServiceImpl;

// The primary abstract base class for developers to implement.
// It follows the RAII pattern and hides implementation details (PIMPL).
class AccessibilityService {
public:
    //========================================================================
    // Public API for the developer
    //========================================================================

    // Returns the executor for posting tasks to the service's main thread.
    [[nodiscard]] auto get_executor() const -> std::shared_ptr<ndk::IThreadExecutor>;

    // Returns service configuration info.
    [[nodiscard]] auto get_service_info() const -> const AccessibilityServiceInfo&;

    // Allows the service to dynamically set its configuration.
    void set_service_info(AccessibilityServiceInfo info);

    // Methods to interact with the system (would be fully implemented).
    // [[nodiscard]] auto get_root_in_active_window() -> std::optional<AccessibilityNodeInfo>;
    // [[nodiscard]] auto get_windows() -> std::vector<AccessibilityWindowInfo>;
    // auto perform_global_action(GlobalAction action) -> bool;

    //========================================================================
    // Callbacks for the developer to override
    //========================================================================

    // Called when a new accessibility event is received.
    virtual void on_accessibility_event(const AccessibilityEvent& event) = 0;

    // Called when the service should stop providing feedback.
    virtual void on_interrupt() = 0;

    // Called once the system has successfully connected to the service.
    // This is the ideal place to perform initial setup.
    virtual void on_service_connected() {} // Optional to override

protected:
    // Constructor initializes the PIMPL object, starting the service logic.
    AccessibilityService();

    // The destructor handles cleanup and disconnection.
    virtual ~AccessibilityService();

    // Rule of Five: Explicitly delete copy/move to prevent slicing
    // and ensure unique ownership of the underlying service connection.
    AccessibilityService(const AccessibilityService&) = delete;
    AccessibilityService& operator=(const AccessibilityService&) = delete;
    AccessibilityService(AccessibilityService&&) = delete;
    AccessibilityService& operator=(AccessibilityService&&) = delete;

private:
    // Pointer to Implementation (PIMPL) to hide all private members
    // and implementation details from the user of the class.
    std::unique_ptr<AccessibilityServiceImpl> impl_;
};

} // namespace accessibility