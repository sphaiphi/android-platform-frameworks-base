// accessibilityservice-internal.cppm
export module accessibilityservice:internal;

import accessibilityservice:types;
import <memory>;
import <expected>;

namespace android {
    class IBinder;
    class IInterface;
    template<typename INTERFACE> class BnInterface;
}

export namespace accessibility::internal {

// Represents a potential IPC communication error.
enum class IpcError {
    transaction_failed,
    service_disconnected
};

/**
 * @class IAccessibilityServiceConnection
 * @brief Internal abstract interface for the Binder/IPC connection to the system service.
 * @details This is an implementation detail and is not exposed to public clients.
 */
class IAccessibilityServiceConnection {
public:
    virtual ~IAccessibilityServiceConnection() = default;

    [[nodiscard]] virtual auto is_accessibility_button_available() const -> std::expected<bool, IpcError> = 0;
    
    // Fingerprint
    [[nodiscard]] virtual auto is_fingerprint_gesture_detection_available() const -> std::expected<bool, IpcError> = 0;

    // Touch Interaction
    virtual auto set_service_detects_gestures_enabled(int display_id, bool mode) -> std::expected<void, IpcError> = 0;
    virtual auto request_touch_exploration(int display_id) -> std::expected<void, IpcError> = 0;
    virtual auto request_dragging(int display_id, int pointer_id) -> std::expected<void, IpcError> = 0;
    virtual auto request_delegating(int display_id) -> std::expected<void, IpcError> = 0;

    // Magnification
    // In a real implementation, we would have full support here.
    // virtual auto get_magnification_config(int display_id) -> std::expected<MagnificationConfig, IpcError> = 0;
    // virtual auto set_magnification_config(int display_id, const MagnificationConfig& config, bool animate) -> std::expected<bool, IpcError> = 0;
};

// Client-side interface for the service to call the system.
// This is what the service uses to perform global actions, get windows, etc.
class BnAccessibilityServiceClient {
public:
    virtual ~BnAccessibilityServiceClient() = default;

    // Called by system to initialize the connection
    virtual void init(std::shared_ptr<IAccessibilityServiceConnection> connection, int connectionId, std::shared_ptr<android::IBinder> windowToken) = 0;

    virtual void onAccessibilityEvent(const AccessibilityEvent& event) = 0;
    virtual void onInterrupt() = 0;
    virtual void onServiceConnected() = 0;
    
    // Internal callbacks for controllers
    virtual void onFingerprintGestureDetectionAvailabilityChanged(bool available) {}
    virtual void onFingerprintGesture(int gesture) {}
};

} // namespace accessibility::internal