# DeviceStateInfo - Reverse Engineering Documentation

## Executive Summary
`DeviceStateInfo` is a snapshot container that holds the complete status of the device state subsystem at a specific point in time. It includes the list of all supported states, the base state (physical/default), and the current committed state (which may be an override).

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable
- **Package**: `android.hardware.devicestate`
- **Relationships**:
    - Contains multiple `DeviceState` objects.
    - Used by `DeviceStateManager` to broadcast state changes to listeners.

## Detailed Functionality

### State Snapshot
Holds three critical pieces of information:
1.  **Supported States**: A list of all valid states this device can enter.
2.  **Base State**: The "physical" state of the device, ignoring software overrides.
3.  **Current State**: The active state, which might be the result of a software override request.

### Diffing
- **`diff(DeviceStateInfo other)`**: Calculates bitwise flags indicating what changed between two snapshots.
    - `CHANGED_SUPPORTED_STATES` (1 << 0)
    - `CHANGED_BASE_STATE` (1 << 1)
    - `CHANGED_CURRENT_STATE` (1 << 2)

## Data Model

### `DeviceStateInfo`
- **Fields**:
    - `supportedStates`: `ArrayList<DeviceState>` (Non-null)
    - `baseState`: `DeviceState` (Non-null)
    - `currentState`: `DeviceState` (Non-null)

## API Reference
- `DeviceStateInfo(ArrayList<DeviceState>, DeviceState, DeviceState)`: Constructor (takes ownership or copy depending on variant).
- `diff(DeviceStateInfo)`: Returns `int` (bitmask).
- `writeToParcel(Parcel, int)`: Serializes the object.

## Java-to-C++ Translation Guide

### Type Mapping
| Java | C++ Equivalent |
|------|----------------|
| `ArrayList<DeviceState>` | `std::vector<DeviceState>` |
| `DeviceState` | `DeviceState` |
| `int` (Flags) | `uint32_t` (Bitmask) |

### Serialization (Parcelable)
Order is critical:
1.  `Int` (Size of supported states)
2.  Loop `size`: `writeTypedObject` (`DeviceState.Configuration`) -> *Note: It writes configurations, not full state objects wrapper*
3.  `writeTypedObject` (`baseState.Configuration`)
4.  `writeTypedObject` (`currentState.Configuration`)

**CRITICAL NOTE**: The Java code deserializes `DeviceState.Configuration` objects and then wraps them in `DeviceState` instances during `createFromParcel`. The C++ implementation must mirror this.

### Memory Management
- Java relies on GC. C++ implementation should likely use `std::vector` for storage and values (or `std::shared_ptr` if `DeviceState` is heavy, though it appears lightweight).

## Test Cases & Validation
- **Diffing**:
    - If `baseState` changes ID 1 -> 2, `diff` must return `CHANGED_BASE_STATE`.
    - If `currentState` changes, `diff` must return `CHANGED_CURRENT_STATE`.
    - If `supportedStates` content or order changes, `diff` must return `CHANGED_SUPPORTED_STATES`.
