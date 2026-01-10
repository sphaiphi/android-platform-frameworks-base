# UsbInterface.java - Reverse Engineering Documentation

## Executive Summary
`UsbInterface` represents a USB Interface Descriptor. It groups a set of endpoints into a functional unit. A USB Configuration can have multiple interfaces.

## Architecture Overview
- **Type**: Data Object / Parcelable
- **Package**: `android.hardware.usb`
- **Relationship**:
  - Child of: `UsbConfiguration`.
  - Parent of: `UsbEndpoint` (Array).

## Detailed Functionality

### Core Fields (USB Descriptor Mapping)
- `mId`: `bInterfaceNumber`.
- `mAlternateSetting`: `bAlternateSetting`.
- `mName`: `iInterface` (String).
- `mClass`: `bInterfaceClass`.
- `mSubclass`: `bInterfaceSubClass`.
- `mProtocol`: `bInterfaceProtocol`.
- `mEndpoints`: Array of `UsbEndpoint`.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mId` | `int` | Interface ID. |
| `mAlternateSetting` | `int` | Alternate Setting ID. |
| `mName` | `String` | Interface Name (Nullable). |
| `mClass` | `int` | Interface Class. |
| `mSubclass` | `int` | Interface Subclass. |
| `mProtocol` | `int` | Interface Protocol. |
| `mEndpoints` | `Parcelable[]` | Array of `UsbEndpoint`. |

## Java-to-C++ Translation Guide

### C++ Struct Suggestion

```cpp
#include <vector>
#include <string>
#include <optional>

struct UsbEndpoint;

struct UsbInterface {
    int id;
    int alternateSetting;
    std::optional<std::string> name;
    int interfaceClass;
    int interfaceSubclass;
    int interfaceProtocol;
    
    std::vector<UsbEndpoint> endpoints;
};
```

### Serialization
- `Parcelable`.
- Writes integers, string, and the endpoint array.

### Alternate Settings
Note that `UsbInterface` objects with the same `mId` but different `mAlternateSetting` are treated as distinct objects in this hierarchy. A `UsbConfiguration` might theoretically contain multiple `UsbInterface` objects that represent the *same* logical interface but different alternate settings, although usually, the API structure implies you iterate active interfaces. The Java `UsbDevice` structure simply lists what is in the config descriptor.
