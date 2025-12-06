// accessibilityservice.cppm
export module accessibilityservice;

import <memory>;
import <functional>;

// Forward-declare dependent types that will be defined elsewhere.
// In a real scenario, these would be imported from their own modules.
export struct EditorInfo;
export class IRemoteAccessibilityInputConnection;

export import :accessibilityservice_types;
export import :accessibility_input_method_session;
export import :accessibility_input_method_session_wrapper;
export import :button_controller_interfaces;
export import ndk_executor; // Export the executor interface for users

export namespace android::accessibilityservice {

// Forward-declare the implementation detail PIMPL class
class AccessibilityServiceImpl;

// The primary abstract base class for developers to implement.
// It follows the RAII pattern and hides implementation details (PIMPL).
class AccessibilityService {
public:
    //========================================================================
    // Public API for the developer
    //========================================================================

    /**
     * @brief Returns the executor for posting tasks to the service's main thread.
     * @return A shared pointer to the thread executor.
     */
    [[nodiscard]] auto get_executor() const -> std::shared_ptr<common::IThreadExecutor>;

    /**
     * @brief Gets the current service configuration information.
     * @return A const reference to the service info.
     */
    [[nodiscard]] auto get_service_info() const -> const AccessibilityServiceInfo&;

    /**
     * @brief Dynamically updates the service's configuration.
     * @param info The new service information to apply.
     */
    void set_service_info(AccessibilityServiceInfo info);

    //========================================================================
    // Callbacks for the developer to override
    //========================================================================

    /**
     * @brief Callback for receiving accessibility events from the system.
     * @param event The event that occurred.
     */
    virtual void on_accessibility_event(const AccessibilityEvent& event) = 0;

    /**
     * @brief Callback requesting the service to interrupt feedback.
     */
    virtual void on_interrupt() = 0;

    /**
     * @brief Called when the system has successfully connected to the service.
     *        This is the ideal place to perform initial setup.
     */
    virtual void on_service_connected() {} // Optional override

    /**
     * @brief Factory callback for creating the input method session.
     * @return A unique_ptr to a developer-defined session implementation.
     */
    virtual auto on_create_input_method_session() -> std::unique_ptr<IAccessibilityInputMethodSession> {
        return nullptr; // Default implementation returns no session
    }

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