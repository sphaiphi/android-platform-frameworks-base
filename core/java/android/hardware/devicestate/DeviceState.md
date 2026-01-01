# DeviceState - Reverse Engineering Documentation

## Executive Summary
`DeviceState` represents a specific configuration of the device hardware and system policies, such as "Folded", "Half-Opened", or "Rear Display Mode". It encapsulates a unique identifier, a name, and a set of properties (both physical and system-level) that define behavior and constraints associated with that state. It is a fundamental data object passed between the System Server and clients.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable
- **Package**: `android.hardware.devicestate`
- **Inner Classes**:
    - `Configuration`: Holds the actual data (identifier, name, properties).
    - `DeviceStateProperties`: Annotation for property constants.
- **Role**: Serves as the currency of the Device State subsystem, allowing the system to map physical hardware configurations (e.g., hinge angle) to system states.

## Detailed Functionality

### State Identification
**Purpose**: Uniquely identify a device state.
- **Identifier**: An integer (`int`) acting as the primary key.
    - Range: `MINIMUM_DEVICE_STATE_IDENTIFIER` (0) to `MAXIMUM_DEVICE_STATE_IDENTIFIER` (10000).
- **Name**: A debug-friendly string description.

### Property System
**Purpose**: Define the characteristics of a state without relying on hardcoded IDs.
- **System Properties**: Rules enforced by the system (e.g., "Cancel when requester not on top").
- **Physical Properties**: Physical characteristics (e.g., "Folded Closed").
- **Storage**: Properties are stored in `ArraySet<Integer>` within the `Configuration` inner class.

### Properties Constants
See `DeviceState.java` for exact values. Key properties include:
- `PROPERTY_FOLDABLE_HARDWARE_CONFIGURATION_FOLD_IN_CLOSED` (1)
- `PROPERTY_POLICY_CANCEL_WHEN_REQUESTER_NOT_ON_TOP` (5)
- `PROPERTY_APP_INACCESSIBLE` (9)
- `PROPERTY_EMULATED_ONLY` (10)
- `PROPERTY_FEATURE_REAR_DISPLAY` (16)

## Data Model

### `DeviceState` (Wrapper)
- **Fields**:
    - `mDeviceStateConfiguration`: `DeviceState.Configuration` (Non-null)

### `DeviceState.Configuration` (Inner Class, Parcelable)
- **Fields**:
    - `mIdentifier`: `int`
    - `mName`: `String` (Non-null)
    - `mSystemProperties`: `ArraySet<Integer>` (Non-null)
    - `mPhysicalProperties`: `ArraySet<Integer>` (Non-null)

## API Reference

### `DeviceState`
- `getIdentifier()`: Returns `int`.
- `getName()`: Returns `String`.
- `hasProperty(int property)`: Returns `boolean` (checks both system and physical sets).
- `hasProperties(int... properties)`: Returns `boolean` (true if ALL properties are present).
- `toString()`: Returns formatted string.
- `equals/hashCode`: Delegates to `Configuration`.

## Java-to-C++ Translation Guide

### Type Mapping
| Java | C++ Equivalent | Notes |
|------|----------------|-------|
| `int` | `int32_t` | Identifiers and Property constants |
| `String` | `std::string` | State names |
| `ArraySet<Integer>` | `std::set<int32_t>` or `std::vector<int32_t>` | Sorted vector preferred for read-only small sets |
| `DeviceState` | `android::hardware::devicestate::DeviceState` | |

### Implementation Notes
1.  **Immutability**: The C++ class should be immutable after construction.
2.  **Parcelable**: Implement `android::os::Parcelable`. The serialization order in `Configuration.writeToParcel` MUST be preserved:
    1.  `Int` (Identifier)
    2.  `String` (Name)
    3.  `ArraySet` (System Properties)
    4.  `ArraySet` (Physical Properties)
3.  **Constants**: Replicate all `PROPERTY_*` constants in a C++ enum or `static constexpr` fields.

### Edge Cases
- **Null Checks**: Java explicitly checks for null `Configuration`. C++ constructor should reference a valid object or handle potential invalid states safely.
- **Identifier Range**: Validate identifier is within [0, 10000].

## Questions for C++ Team
- Should we use a bitmask for properties if the set of properties is small and stable, or stick to `std::vector`/`std::set` to match the extensibility of `ArraySet`? (Java uses `ArraySet`, implying sparse/extensible values).
