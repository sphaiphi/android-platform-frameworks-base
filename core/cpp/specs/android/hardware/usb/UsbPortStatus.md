# UsbPortStatus.java - Reverse Engineering Documentation

## Executive Summary
`UsbPortStatus` is an immutable snapshot of the state of a `UsbPort` at a specific point in time. It contains current mode, roles, compliance warnings, and Type-C specific status (contaminant, power bricks, DisplayPort).

## Architecture Overview
- **Type**: Data Object / Parcelable
- **Package**: `android.hardware.usb`
- **Annotation**: `@Immutable`.

## Detailed Functionality

### State Fields
- **Modes/Roles**: `mCurrentMode`, `mCurrentPowerRole`, `mCurrentDataRole`.
- **Capabilities**: `mSupportedRoleCombinations`.
- **Contaminant**: `mContaminantProtectionStatus`, `mContaminantDetectionStatus`.
- **Data Status**: `mUsbDataStatus` (Enabled/Disabled reasons like Overheat, Dock, etc.).
- **Power**: `mPowerTransferLimited`, `mPowerBrickConnectionStatus`.
- **Warnings**: `mComplianceWarnings` (Array of issues like "Missing Rp", "Input Power Limited").
- **Plug**: `mPlugState` (Orientation).
- **Alt Mode**: `mDisplayPortAltModeInfo`.

### Data Handling
- **Constructor Logic**: Handles legacy behavior where `DATA_STATUS_DISABLED_DOCK` is inferred from sub-flags (`DOCK_HOST_MODE` / `DOCK_DEVICE_MODE`).

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mCurrentMode` | `int` | DFP/UFP/etc. |
| `mCurrentPowerRole` | `int` | Source/Sink. |
| `mCurrentDataRole` | `int` | Host/Device. |
| `mUsbDataStatus` | `int` | Bitmask of enablement status. |
| `mDisplayPortAltModeInfo` | `DisplayPortAltModeInfo` | Nested Parcelable. |

## Java-to-C++ Translation Guide

### C++ Struct Suggestion

```cpp
struct UsbPortStatus {
    int currentMode;
    int currentPowerRole;
    int currentDataRole;
    int supportedRoleCombinations;
    int contaminantProtectionStatus;
    int contaminantDetectionStatus;
    int usbDataStatus;
    bool powerTransferLimited;
    int powerBrickConnectionStatus;
    std::vector<int> complianceWarnings;
    int plugState;
    std::optional<DisplayPortAltModeInfo> displayPortAltModeInfo;
};
```

### Serialization
- `Parcelable` implementation.
- Note the boolean flag handling for the optional `mDisplayPortAltModeInfo`.

### Constants
Large number of `int` constants for Enums. These should be mapped to C++ `enum class` or `constexpr` definitions.
