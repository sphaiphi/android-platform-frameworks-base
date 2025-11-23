// accessibility_button_interfaces.cppm
export module accessibilityservice:button_controller_interfaces;

import <memory>;
import <functional>;

export namespace accessibility {

// Forward declaration
class IAccessibilityButtonController;

/**
 * @class IAccessibilityButtonCallback
 * @brief Interface for receiving callbacks about the accessibility button.
 * @details Clients must implement this interface to handle button events. The
 *          lifetime of the callback object is managed by the client. It must
 *          be unregistered before being destroyed.
 */
class IAccessibilityButtonCallback {
public:
    virtual ~IAccessibilityButtonCallback() = default;

    /**
     * @brief Called when the accessibility button is clicked.
     * @param controller A non-owning pointer to the controller that dispatched the event.
     */
    virtual void on_clicked(IAccessibilityButtonController* controller) = 0;

    /**
     * @brief Called when the button's availability to the service changes.
     * @param controller A non-owning pointer to the controller that dispatched the event.
     * @param available True if the button is now available, false otherwise.
     */
    virtual void on_availability_changed(IAccessibilityButtonController* controller, bool available) = 0;
};


/**
 * @class IAccessibilityButtonController
 * @brief Interface for interacting with the system accessibility button.
 * @details Provides methods to check availability and manage callbacks for button events.
 */
class IAccessibilityButtonController {
public:
    virtual ~IAccessibilityButtonController() = default;

    /**
     * @brief Synchronously checks if the accessibility button is available.
     * @return True if the button is available and the service can use it, false otherwise.
     *         Returns false in case of an IPC error.
     */
    [[nodiscard]] virtual auto is_accessibility_button_available() const -> bool = 0;

    /**
     * @brief Registers a callback for accessibility button events.
     * @param callback A non-owning pointer to the client's callback implementation.
     *        The client MUST ensure the callback's lifetime exceeds its registration period.
     * @param executor A shared pointer to the thread executor on which to run the callback.
     */
    virtual void register_accessibility_button_callback(
        IAccessibilityButtonCallback* callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) = 0;

    /**
     * @brief Unregisters a previously registered callback.
     * @param callback The non-owning pointer to the callback to remove. It is safe
     *        to call this with a callback that was not registered.
     */
    virtual void unregister_accessibility_button_callback(IAccessibilityButtonCallback* callback) = 0;
};

} // namespace accessibility