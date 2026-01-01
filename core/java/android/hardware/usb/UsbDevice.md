# UsbDevice.java - Reverse Engineering Documentation

## Executive Summary
`UsbDevice` represents a connected USB device. It serves as the root of the USB descriptor hierarchy (Device -> Configuration -> Interface -> Endpoint) available to Java applications. It contains device identity (VID/PID), strings, capabilities, and the full tree of configurations.

## Architecture Overview
- **Type**: Data Object / Parcelable
- **Package**: `android.hardware.usb`
- **Dependencies**:
  - `IUsbSerialReader`: For secure serial number access.
  - `UsbConfiguration`: Child nodes.
  - `UsbInterface`: Helper accessors.

## Detailed Functionality

### Core Fields
- **Identity**: `mVendorId`, `mProductId`, `mName` (Device path, e.g., `/dev/bus/usb/001/002`).
- **Descriptors**: `mClass`, `mSubclass`, `mProtocol` (Device level).
- **Strings**: `mManufacturerName`, `mProductName`, `mVersion`.
- **Serial**: `mSerialNumberReader` (Binder).
- **Hierarchy**: `mConfigurations` (Array of configurations).
- **Capabilities**: Boolean flags for `mHasAudioPlayback`, `mHasAudioCapture`, `mHasMidi`, `mHasVideoPlayback`, `mHasVideoCapture`.

### Interface Flattening
The class provides `getInterfaceList()` which flattens the hierarchy.
- It iterates all `UsbConfiguration`s.
- It collects all `UsbInterface`s into a single linear array `mInterfaces`.
- This is lazily initialized.

### Native Methods
- `native_get_device_id(String name)`: Returns static integer ID.
- `native_get_device_name(int id)`: Returns string path.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mName` | `String` | Device filesystem path. |
| `mVendorId` | `int` | VID. |
| `mProductId` | `int` | PID. |
| `mClass` | `int` | Device Class. |
| `mSubclass` | `int` | Device Subclass. |
| `mProtocol` | `int` | Device Protocol. |
| `mManufacturerName` | `String` | Nullable. |
| `mProductName` | `String` | Nullable. |
| `mVersion` | `String` | Device Version (bcdDevice). |
| `mConfigurations` | `UsbConfiguration[]` | Array of configs. |
| `mSerialNumberReader` | `IUsbSerialReader` | Binder. |

## API Reference
- `getDeviceName()`: Returns the path.
- `getInterface(int)`: Returns from the flattened list across all configurations.
- `getDeviceId()`: Returns unique integer ID (not persistent across disconnects).

## Java-to-C++ Translation Guide

### C++ Class Suggestion
The structure mirrors `libusb_device_descriptor` but with pre-parsed strings and children.

```cpp
class UsbDevice {
public:
    std::string name; // Path
    int vendorId;
    int productId;
    int deviceClass;
    int deviceSubclass;
    int deviceProtocol;
    std::string manufacturer;
    std::string product;
    std::string version;
    
    std::vector<UsbConfiguration> configurations;
    
    // Derived/Flattened
    std::vector<UsbInterface> getAllInterfaces() const;
    
    // Serial handling via Binder interface or string if local
};
```

### Flattening Logic
The `getInterface(int index)` API in Java abstracts away which Configuration an Interface belongs to. In C++, if supporting this API, you must implement the same flattening loop: iterate configs, iterate their interfaces, and index globally.

### JNI / Native
The native methods `native_get_device_id` and `native_get_device_name` likely look up mapping in the `UsbDeviceManager` service or `libusbhost`.

## Builder Pattern
There is a static inner `Builder` class used by the service to construct `UsbDevice` instances. This implies `UsbDevice` is immutable once built.
