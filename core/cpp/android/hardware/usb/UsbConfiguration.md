# UsbConfiguration.java - Reverse Engineering Documentation

## Executive Summary
`UsbConfiguration` represents a USB Configuration Descriptor as defined in the USB 2.0/3.0 specifications. It contains hierarchy information: a configuration has one or more `UsbInterface`s, which in turn have `UsbEndpoint`s.

## Architecture Overview
- **Type**: Data Object / Parcelable
- **Package**: `android.hardware.usb`
- **Relationship**:
  - Child of: `UsbDevice`
  - Parent of: `UsbInterface` (Array)

## Detailed Functionality

### Core Fields (USB Descriptor Mapping)
Matches standard USB Configuration Descriptor fields:
- `mId`: `bConfigurationValue` (The value used to select this configuration).
- `mName`: `iConfiguration` (String descriptor index resolved to string).
- `mAttributes`: `bmAttributes` (Bitmap).
- `mMaxPower`: `bMaxPower` (Expressed in original descriptor units, but note the getter logic).

### Attributes Logic
- **Self Powered**: Bit 6 (`1 << 6`).
- **Remote Wakeup**: Bit 5 (`1 << 5`).

### Power Calculation
- `getMaxPower()`: The Java method returns the power in **milliamps**.
  - **Note**: The USB descriptor stores power in 2mA units. The Java code performs `mMaxPower * 2`.
  - **Warning**: `mMaxPower` field stores the raw value (units of 2mA).

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mId` | `int` | Configuration Value. |
| `mName` | `String` | Configuration Name (nullable). |
| `mAttributes` | `int` | Bitmask. |
| `mMaxPower` | `int` | Raw value (2mA units). |
| `mInterfaces` | `Parcelable[]` | Array of `UsbInterface`. |

## API Reference
- `isSelfPowered()`: Checks bit 6 of attributes.
- `isRemoteWakeup()`: Checks bit 5 of attributes.
- `getInterface(int)`: Accessor for interfaces.

## Java-to-C++ Translation Guide

### C++ Struct Suggestion

```cpp
#include <vector>
#include <string>
#include <optional>

struct UsbInterface;

struct UsbConfiguration {
    int id;
    std::optional<std::string> name;
    int attributes;
    int maxPowerRaw; // Keep raw to match Java's storage
    
    std::vector<UsbInterface> interfaces;

    bool isSelfPowered() const { return (attributes & (1 << 6)) != 0; }
    bool isRemoteWakeup() const { return (attributes & (1 << 5)) != 0; }
    int getMaxPowerMa() const { return maxPowerRaw * 2; }
};
```

### Serialization
- `Parcelable` implementation.
- Writes: Id, Name, Attributes, MaxPower, Interface Array.

### Implementation Risks
- **Max Power**: Ensure clarity between "raw value" (from descriptor) and "milliamps" (API return value).
- **Interface Array**: The `setInterfaces` method is used during construction/unparcelling to populate the children. C++ construction should probably happen in one pass or allow building up the vector.
