# UsbEndpoint.java - Reverse Engineering Documentation

## Executive Summary
`UsbEndpoint` represents a USB Endpoint Descriptor. It defines the point of data transfer (IN or OUT) and the type of transfer (Bulk, Control, Interrupt, Isochronous).

## Architecture Overview
- **Type**: Data Object / Parcelable
- **Package**: `android.hardware.usb`
- **Relationship**: Child of `UsbInterface`.

## Detailed Functionality

### Core Fields (USB Descriptor Mapping)
- `mAddress`: `bEndpointAddress` (Contains Endpoint Number and Direction).
- `mAttributes`: `bmAttributes` (Contains Transfer Type).
- `mMaxPacketSize`: `wMaxPacketSize`.
- `mInterval`: `bInterval`.

### Helper Methods
- `getEndpointNumber()`: Address & `0x0F`.
- `getDirection()`: Address & `0x80` (`USB_DIR_IN` / `USB_DIR_OUT`).
- `getType()`: Attributes & `0x03` (Control, Isoc, Bulk, Int).

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mAddress` | `int` | Address (Num | Dir). |
| `mAttributes` | `int` | Attributes (Type). |
| `mMaxPacketSize` | `int` | Max packet size. |
| `mInterval` | `int` | Polling interval. |

## Java-to-C++ Translation Guide

### C++ Struct Suggestion

```cpp
struct UsbEndpoint {
    int address;
    int attributes;
    int maxPacketSize;
    int interval;

    int getNumber() const { return address & 0x0F; }
    int getDirection() const { return address & 0x80; }
    int getType() const { return attributes & 0x03; }
};
```

### Serialization
- `Parcelable` implementation.
- Simple integer write.

## API Notes
- Isochronous endpoints are noted as "currently unsupported" in the JavaDoc, but the class extracts the type correctly. The support limitation is likely in `UsbDeviceConnection` / `UsbRequest` handling of ISO transfers.
