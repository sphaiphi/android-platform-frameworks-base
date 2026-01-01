# UsbPort.java - Reverse Engineering Documentation

## Executive Summary
`UsbPort` represents a physical USB connector (specifically Type-C). It is a handle used to query status (`UsbPortStatus`) and perform operations like role switching, data enabling, and power limiting.

## Architecture Overview
- **Type**: Data Object / Handle
- **Package**: `android.hardware.usb`
- **Dependencies**: 
  - `UsbManager`: Back-reference to perform operations.
  - `UsbPortStatus`: The state object.

## Detailed Functionality

### Identification & Capabilities
- `mId`: Unique string ID (e.g., "port0").
- `mSupportedModes`: Bitmask (DFP, UFP, Dual, Audio/Debug Accessory).
- `mSupportedContaminantProtectionModes`: Bitmask.
- `mSupportsEnableContaminantPresenceProtection/Detection`: Booleans.
- `mSupportedAltModes`: Bitmask (DisplayPort).

### Operations (Proxy to Manager)
- `setRoles`: Changes power/data roles.
- `resetUsbPort`: Resets the port.
- `enableUsbData`: Enables/Disables data pins.
- `enableLimitPowerTransfer`: Limits charging current.
- `enableContaminantDetection`.

### Async Pattern
Operations like `resetUsbPort` and `enableUsbData` use `UsbOperationInternal` to handle the asynchronous result from the HAL/Service. They return status codes defined in `UsbPort` (e.g., `ENABLE_USB_DATA_SUCCESS`).

## Data Model
Holds static configuration/capabilities. Dynamic state is in `UsbPortStatus`.

## Constants
Defines numerous status codes for operation results (`ERROR_INTERNAL`, `ERROR_NOT_SUPPORTED`, `ERROR_PORT_MISMATCH`, etc.) and mode constants (`MODE_DFP`, `MODE_UFP`, etc.).

## Java-to-C++ Translation Guide
- **Handle Pattern**: This is effectively a client-side handle containing the Port ID.
- **Operations**: Each method calls into `UsbManager`. In C++, this would call into the `IUsbManager` binder interface passing the port ID.

## API Notes
- `isPdCompliant()`: Helper checking if all role combinations are supported.
- `combineRolesAsBit`: Helper to pack power/data roles into a bitmask.

## C++ Implementation Guidance
Keep this class as a lightweight wrapper around the Port ID and the `IUsbManager` pointer.
