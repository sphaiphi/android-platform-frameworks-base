# UsbConstants.java - Reverse Engineering Documentation

## Executive Summary
`UsbConstants` defines standard constants related to the USB specification (linux/usb/ch9.h) and Android-specific mappings. It includes endpoint directions, types, and standard USB class codes.

## Architecture Overview
- **Type**: Constant Definition Class
- **Package**: `android.hardware.usb`
- **Dependencies**: `android.service.ServiceProtoEnums` (Maps internal proto enums to public API constants).

## Constants Reference

### Endpoint Direction (`bmAttributes` direction bit)
- `USB_DIR_OUT` (0)
- `USB_DIR_IN` (0x80)
- `USB_ENDPOINT_DIR_MASK` (0x80)

### Endpoint Type (`bmAttributes` transfer type)
- `USB_ENDPOINT_XFER_CONTROL` (0)
- `USB_ENDPOINT_XFER_ISOC` (1)
- `USB_ENDPOINT_XFER_BULK` (2)
- `USB_ENDPOINT_XFER_INT` (3)
- `USB_ENDPOINT_XFERTYPE_MASK` (0x03)

### Endpoint Number
- `USB_ENDPOINT_NUMBER_MASK` (0x0f)

### Control Request Types (`bmRequestType`)
- `USB_TYPE_MASK` (0x03 << 5)
- `USB_TYPE_STANDARD` (0x00 << 5)
- `USB_TYPE_CLASS` (0x01 << 5)
- `USB_TYPE_VENDOR` (0x02 << 5)
- `USB_TYPE_RESERVED` (0x03 << 5)

### USB Classes (`bDeviceClass` / `bInterfaceClass`)
- `USB_CLASS_PER_INTERFACE` (0)
- `USB_CLASS_AUDIO` (1)
- `USB_CLASS_COMM` (2)
- `USB_CLASS_HID` (3)
- `USB_CLASS_PHYSICA` (5)
- `USB_CLASS_STILL_IMAGE` (6)
- `USB_CLASS_PRINTER` (7)
- `USB_CLASS_MASS_STORAGE` (8)
- `USB_CLASS_HUB` (9)
- `USB_CLASS_CDC_DATA` (0x0a)
- `USB_CLASS_CSCID` (0x0b)
- `USB_CLASS_CONTENT_SEC` (0x0d)
- `USB_CLASS_VIDEO` (0x0e)
- `USB_CLASS_WIRELESS_CONTROLLER` (0xe0)
- `USB_CLASS_MISC` (0xef)
- `USB_CLASS_APP_SPEC` (0xfe)
- `USB_CLASS_VENDOR_SPEC` (0xff)

## Java-to-C++ Translation Guide
This file maps almost directly to standard C headers.
- **Suggestion**: Use `linux/usb/ch9.h` or standard system headers where possible to avoid redefinition.
- If a standalone header is needed, define `constexpr` values.

```cpp
namespace android::hardware::usb {
    constexpr int kUsbDirOut = 0;
    constexpr int kUsbDirIn = 0x80;
    // ... etc
}
```
