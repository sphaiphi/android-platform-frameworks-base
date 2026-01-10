# DisplayPortAltModeInfo.java - Reverse Engineering Documentation

## Executive Summary
`DisplayPortAltModeInfo` is a simple data carrier (Parcelable) that holds status information about USB-C DisplayPort Alternate Mode. It captures the state of the partner sink, cable, lane count, hot-plug detection, and link training status.

## Architecture Overview
- **Type**: Data Object / Parcelable
- **Package**: `android.hardware.usb`
- **Annotations**: `@SystemApi`, `@Immutable` (implicitly via design)

## Data Model

| Field | Java Type | C++ Equivalent | Description |
|-------|-----------|----------------|-------------|
| `mPartnerSinkStatus` | `int` (Enum) | `enum DisplayPortAltModeStatus` | Status of the connected sink. |
| `mCableStatus` | `int` (Enum) | `enum DisplayPortAltModeStatus` | Status of the connecting cable. |
| `mNumLanes` | `int` | `int` | Number of active DisplayPort lanes. |
| `mHotPlugDetect` | `boolean` | `bool` | HPD signal state. |
| `mLinkTrainingStatus` | `int` (Enum) | `enum LinkTrainingStatus` | Result of link training. |

### Enums

**DisplayPortAltModeStatus**:
- `DISPLAYPORT_ALT_MODE_STATUS_UNKNOWN` (0)
- `DISPLAYPORT_ALT_MODE_STATUS_NOT_CAPABLE` (1)
- `DISPLAYPORT_ALT_MODE_STATUS_CAPABLE_DISABLED` (2)
- `DISPLAYPORT_ALT_MODE_STATUS_ENABLED` (3)

**LinkTrainingStatus**:
- `LINK_TRAINING_STATUS_UNKNOWN` (0)
- `LINK_TRAINING_STATUS_SUCCESS` (1)
- `LINK_TRAINING_STATUS_FAILURE` (2)

## API Reference
- Getters for all fields (`getPartnerSinkStatus`, `getCableStatus`, etc.).
- `toString()` for human-readable output mapping constants to strings.
- Parcelable implementation for IPC.

## Java-to-C++ Translation Guide

### C++ Struct Definition

```cpp
enum class DisplayPortAltModeStatus : int {
    Unknown = 0,
    NotCapable = 1,
    CapableDisabled = 2,
    Enabled = 3
};

enum class LinkTrainingStatus : int {
    Unknown = 0,
    Success = 1,
    Failure = 2
};

struct DisplayPortAltModeInfo {
    DisplayPortAltModeStatus partnerSinkStatus;
    DisplayPortAltModeStatus cableStatus;
    int numLanes;
    bool hotPlugDetect;
    LinkTrainingStatus linkTrainingStatus;
    
    // Serialization logic (Parcel equivalent) would go here
};
```

### Serialization
This class implements `Parcelable`. If this data needs to be passed between processes in C++, it likely needs to implement the Android Binder `Parcel` read/write protocol matching the Java implementation:
1. `writeInt` (partnerSinkStatus)
2. `writeInt` (cableStatus)
3. `writeInt` (numLanes)
4. `writeBoolean` (hotPlugDetect)
5. `writeInt` (linkTrainingStatus)

## Implementation Risks
- Ensure the integer values for the enums match the Java constants exactly, as they are part of the system API contract.
