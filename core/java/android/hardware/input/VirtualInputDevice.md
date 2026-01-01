# VirtualInputDevice - Reverse Engineering Documentation

## Executive Summary
`VirtualInputDevice` is the abstract base class for all virtual input devices. It handles the lifecycle (creation/closing) and identity (token/deviceId) management.

## Architecture Overview
- **Resources**: Holds `IVirtualDevice` (Binder interface to service) and `IBinder` (Token).
- **Config**: Holds `VirtualInputDeviceConfig`.
- **Closeable**: Implements `AutoCloseable` to unregister the device.

## Detailed Functionality
- **Constructor**: Stores references.
- **getInputDeviceId()**: Queries the system server for the assigned Input Device ID.
- **close()**: Calls `mVirtualDevice.unregisterInputDevice(mToken)`.

## Java-to-C++ Translation Guide
- **Base Class**: C++ abstract base class.
- **Destructor**: Handle `unregister` logic.

## Implementation Risks
- Ensuring `close()` is called to prevent resource leaks on the system server.
