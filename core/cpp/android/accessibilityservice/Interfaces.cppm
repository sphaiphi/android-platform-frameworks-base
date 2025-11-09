export module accessibility.interfaces;

import std.core;
import <functional>;
import <memory>;
import <optional>;
import <stdexcept>;

namespace android;
namespace android::accessibility {

// Forward-declare the controller class, as it's used in the callback interface.
export class AccessibilityButtonController;

/**
 * @brief Abstract interface for a client to implement, receiving button events.
 * @note The client owns the callback object and is responsible for unregistering it
 *       before destruction to prevent use-after-free errors.
 */
export class AccessibilityButtonCallback {
public:
    virtual ~AccessibilityButtonCallback() = default;
    virtual void on_clicked(AccessibilityButtonController* controller) = 0;
    virtual void on_availability_changed(AccessibilityButtonController* controller, bool available) = 0;
};

/**
 * @brief Abstract interface for an IPC connection to the remote system service.
 */
export class IAccessibilityServiceConnection {
public:
    virtual ~IAccessibilityServiceConnection() = default;
    [[nodiscard]] virtual auto is_accessibility_button_available() -> std::optional<bool> = 0;
};



// braille.cppm

export namespace braille::hid {

using Executor = std::function<void(std::function<void()>)>;

struct BluetoothDeviceHandle {
    std::string id;
    auto operator<=>(const BluetoothDeviceHandle&) const = default;
};

struct UsbDeviceHandle {
    int vendor_id;
    int product_id;
    auto operator<=>(const UsbDeviceHandle&) const = default;
};

enum class ErrorCode : std::uint32_t {
    none = 0,
    cannot_access = 1 << 0,
    display_not_found = 1 << 1,
    unknown = 1 << 31,
};

constexpr auto operator|(ErrorCode lhs, ErrorCode rhs) -> ErrorCode {
    using T = std::underlying_type_t<ErrorCode>;
    return static_cast<ErrorCode>(static_cast<T>(lhs) | static_cast<T>(rhs));
}
constexpr auto operator&(ErrorCode lhs, ErrorCode rhs) -> ErrorCode {
    using T = std::underlying_type_t<ErrorCode>;
    return static_cast<ErrorCode>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

struct FeatureDisabledError : std::runtime_error {
    FeatureDisabledError() : std::runtime_error("Braille Display HID feature is disabled.") {}
};
struct SecurityError : std::runtime_error {
    explicit SecurityError(const std::string& msg) : std::runtime_error(msg) {}
};
struct IOError : std::runtime_error {
    explicit IOError(const std::string& msg) : std::runtime_error(msg) {}
};

class BrailleDisplayCallback {
public:
    virtual ~BrailleDisplayCallback() = default;
    virtual void on_connected(std::span<const std::uint8_t> hid_descriptor) = 0;
    virtual void on_connection_failed(ErrorCode error_flags) = 0;
    virtual void on_input(std::span<const std::uint8_t> input) = 0;
    virtual void on_disconnected() = 0;
};

class BrailleDisplayController {
public:
    virtual ~BrailleDisplayController() = default;
    virtual void connect(const BluetoothDeviceHandle& device, BrailleDisplayCallback& callback, Executor executor = {}) = 0;
    virtual void connect(const UsbDeviceHandle& device, BrailleDisplayCallback& callback, Executor executor = {}) = 0;
    [[nodiscard]] virtual auto is_connected() const noexcept -> bool = 0;
    virtual void write(std::span<const std::uint8_t> buffer) = 0;
    virtual void disconnect() noexcept = 0;
};

[[nodiscard]] auto create_mock_controller() -> std::unique_ptr<BrailleDisplayController>;

} // namespace braille::hid
}