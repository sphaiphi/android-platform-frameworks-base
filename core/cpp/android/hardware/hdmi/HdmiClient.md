# HdmiClient - Reverse Engineering Documentation

## Executive Summary
`HdmiClient` is an abstract base class for all HDMI-CEC logical device clients (`HdmiTvClient`, `HdmiPlaybackClient`, etc.). It encapsulates common interactions with the system service `IHdmiControlService`.

## Architecture Overview
- **Type**: Abstract Base Class.
- **System API**: Yes (`@SystemApi`).
- **Communication**: Holds reference to `IHdmiControlService`.

## Detailed Functionality

### Device Selection & Active Source
- `selectDevice(int logicalAddress, ...)`: Requests the service to make a device the active source. Wraps the callback.
- `getActiveSource()`: Synchronously retrieves `HdmiDeviceInfo` of the current active source.

### Messaging
- `sendKeyEvent(int keyCode, boolean isPressed)`: Sends CEC `<User Control Pressed>` or `<User Control Released>`.
- `sendVolumeKeyEvent(int keyCode, boolean isPressed)`: Sends volume keys to the primary audio receiver.
- `sendVendorCommand(int targetAddress, byte[] params, boolean hasVendorId)`: Sends vendor-specific commands.

### Listener Management
- `setVendorCommandListener(VendorCommandListener listener, int vendorId)`: Registers a callback for incoming vendor commands. Can filter by Vendor ID. Wraps `VendorCommandListener` into `IHdmiVendorCommandListener` stub.

### Abstract Methods
- `getDeviceType()`: Must be implemented by subclasses to return the CEC device type.

## Data Model
- **Service**: `IHdmiControlService mService`.
- **Constants**: `UNKNOWN_VENDOR_ID` (0xFFFFFF).

## API Reference
- `selectDevice`
- `getActiveSource`
- `sendKeyEvent`
- `sendVolumeKeyEvent`
- `sendVendorCommand`
- `setVendorCommandListener`

## Java-to-C++ Translation Guide
- **Base Class**: Create a C++ base class `HdmiClient`.
- **Callbacks**: Use `std::function` or interface classes for `OnDeviceSelectedListener` and `VendorCommandListener`.
- **Binder**: The C++ implementation will likely interact with the Binder proxy of `IHdmiControlService`.

## Implementation Risks
- **Callback Wrappers**: Ensure proper lifecycle management of callback wrappers (Stubs) passed to the service. Java uses anonymous inner classes; C++ might need `sp<IHdmiControlCallback>` objects.
