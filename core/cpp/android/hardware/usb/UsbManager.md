# UsbManager - Reverse Engineering Documentation

## Executive Summary
`UsbManager` is the central system service for managing USB state and communication. it supports both "Host Mode" (Android acting as a host for peripherals like mice or cameras) and "Device Mode" (Android acting as a peripheral for a PC). It handles device discovery, permission management, and port configuration (including power and data role switching).

## Architecture Overview
- **Service Type**: System-level service retrieved via `Context.USB_SERVICE`.
- **Backend Interaction**: Communicates with the `IUsbManager` (native `UsbService`) via Binder.
- **Port Management**: Uses `UsbPort` and `UsbPortStatus` to manage physical connections and roles.
- **Accessory Support**: Implements the Android Open Accessory (AOA) protocol for communicating with specialized hardware.

## Detailed Functionality

### Host Mode Operations
**Purpose**: To interact with attached USB peripherals.
**Algorithm**:
1. Call `getDeviceList()` to find attached hardware.
2. Call `requestPermission(UsbDevice, PendingIntent)` to get user consent.
3. Call `openDevice(UsbDevice)` to obtain a `UsbDeviceConnection` for data transfer.

### Device/Gadget Mode Configuration
**Purpose**: To control how Android presents itself to a USB host.
**Functions**: Supports `MTP`, `PTP`, `RNDIS` (Tethering), `MIDI`, `ADB`, and `UVC` (Webcam mode).
**Algorithm**: Use `setCurrentFunctions(long)` to set the active bitmask of enabled features.

### Port and Power Control
**Purpose**: To manage USB-C features like role switching and compliance.
**Methods**:
- `getPorts()`: List physical USB ports.
- `setPortRoles(UsbPort, powerRole, dataRole)`: Manually trigger role swaps.
- `enableContaminantDetection()`: Toggle safety algorithms for moisture/debris detection.

## Data Model

### Constants
- `ACTION_USB_STATE`: Sticky broadcast for device mode status changes.
- `USB_FUNCTION_*`: Flags for different gadget modes.
- `USB_DATA_TRANSFER_RATE_*`: Bandwidth constants from 1.5Mbps to 40Gbps.

### Internal Handles
- `AccessoryHandle`: Manages the lifecycle of file descriptors for AOA accessories.
- `mDisplayPortListeners`: Tracks apps listening for DisplayPort Alt Mode events.

## API Reference

### Public Methods
- `HashMap<String, UsbDevice> getDeviceList()`: Discovery.
- `UsbDeviceConnection openDevice(UsbDevice device)`: Data access.
- `void requestPermission(UsbDevice device, PendingIntent pi)`: Security.
- `void setTorchMode(String cameraId, boolean enabled)`: Flashlight control.
- `List<UsbPort> getPorts()`: Hardware topology.

## Java-to-C++ Translation Guide

### Service Discovery
- **Java**: `Context.getSystemService`.
- **C++**: Use `android::IServiceManager` to find the `usb` service and obtain an `android::hardware::usb::IUsbManager` binder.

### File Descriptor Passing
- **Java**: `ParcelFileDescriptor`.
- **C++**: Use `android::base::unique_fd` to manage ownership of file descriptors received via Binder (`openDevice` returns an FD).

### Event Dispatch
- **Java**: Sticky broadcasts and `Executor`-based listeners.
- **C++**: Implement a `BnUsbManagerCallback` or similar to receive events from the service and dispatch them to a native event loop.

## Test Cases & Validation
1. **Device Attach/Detach**: Plug in a USB mouse and verify `ACTION_USB_DEVICE_ATTACHED` is received with a valid `UsbDevice` object.
2. **Role Switching**: On a supported USB-C device, use `setPortRoles` to switch from Sink to Source and verify the power direction change via a hardware tester.
3. **Bandwidth Query**: Verify `getUsbBandwidthMbps()` returns the correct speed (e.g., 480 for High Speed) when connected to a host.

## Implementation Risks
- **Permission Leaks**: Ensuring that USB permissions are revoked when a device is detached is critical for security.
- **Async Failures**: Many USB operations (like role swaps) are asynchronous and can fail deep in the kernel; the C++ implementation must handle these timeouts and hardware errors.
- **Gadget Reset**: `resetUsbGadget()` forces a full stack reset which can be disruptive to adb or other active connections.