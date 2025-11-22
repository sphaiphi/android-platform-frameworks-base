// braille_display_interfaces.cppm
export module braille_display_interfaces;

import <vector>;
import <cstdint>;
import <string>;
import <variant>;
import <expected>;

// SAFETY ✓ Type: Strong types used for all domain concepts.
export namespace accessibility {

// Opaque handles for different device types.
struct BluetoothDevice {
    std::string address;
    auto operator<=>(const BluetoothDevice&) const = default;
};

struct UsbDevice {
    int vendor_id;
    int product_id;
    auto operator<=>(const UsbDevice&) const = default;
};

using Device = std::variant<BluetoothDevice, UsbDevice>;

// Strong type for HID data buffers.
using HidData = std::vector<uint8_t>;

// Strong type for the error codes mentioned in the documentation.
// SAFETY ✓ Type: enum class provides type-safe, scoped enumerations.
export enum class ConnectError {
    cannot_access = 1 << 0,
    display_not_found = 1 << 1,
    already_connected = 1 << 2,
    feature_disabled = 1 << 3,
};

// The observer interface clients must implement.
// The lifetime of the callback handler must exceed that of the controller.
class BrailleDisplayCallback {
public:
    virtual ~BrailleDisplayCallback() = default;
    virtual void on_connected(const HidData& hid_descriptor) = 0;
    virtual void on_connection_failed(ConnectError error) = 0;
    virtual void on_input_received(const HidData& input) = 0;
    virtual void on_disconnected() = 0;
};

// The main controller interface.
class BrailleDisplayController {
public:
    virtual ~BrailleDisplayController() = default;

    // Asynchronously connects to a device.
    // Returns immediately. The result is delivered via the callback.
    [[nodiscard]] virtual auto connect(Device device, BrailleDisplayCallback* callback)
        -> std::expected<void, ConnectError> = 0;

    // Asynchronously sends data to the display. "Fire and forget".
    // Throws std::logic_error if not connected.
    virtual void write(const HidData& buffer) = 0;

    // Disconnects from the current device. Safe to call if not connected.
    virtual void disconnect() = 0;

    // Thread-safe check of the connection status.
    [[nodiscard]] virtual auto is_connected() const -> bool = 0;
};

} // namespace accessibility