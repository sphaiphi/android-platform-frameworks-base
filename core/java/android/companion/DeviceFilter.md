# DeviceFilter - Reverse Engineering Documentation

## Executive Summary
`DeviceFilter` is a generic interface defining the contract for objects that filter companion devices during discovery. It abstracts the matching logic for different communication mediums (Bluetooth, BLE, Wi-Fi).

## Architecture Overview
- **Type Parameter**: `<D extends Parcelable>` - The type of device being filtered (e.g., `BluetoothDevice`).
- **Inheritance**: Extends `Parcelable`.
- **Implementations**: `BluetoothDeviceFilter`, `BluetoothLeDeviceFilter`, `WifiDeviceFilter`.

## Detailed Functionality

### Interface Contract
**Purpose**: To allow polymorphic filtering across different discovery stacks.
**Methods**:
- `matches(D device)`: Determines if a specific device instance satisfies the filter criteria.
- `getDeviceDisplayName(D device)`: Provides a medium-specific human-readable name for the device.
- `getMediumType()`: Returns an integer indicating the medium (BT, BLE, or Wi-Fi).

### Static Helpers
- `matches(DeviceFilter<D> filter, D device)`: A null-safe utility that returns true if the filter is null (default allow).

## Data Model
- `MEDIUM_TYPE_BLUETOOTH` (0)
- `MEDIUM_TYPE_BLUETOOTH_LE` (1)
- `MEDIUM_TYPE_WIFI` (2)

## Java-to-C++ Translation Guide
- **Interface**: Use an abstract base class `IDeviceFilter` with a virtual `matches` method.
- **Generics**: Since C++ is statically typed, use a base `Device` type if possible, or implement a `std::variant` based filter logic.
- **Medium Type**: Use an `enum class MediumType`.

## Implementation Risks
- **Parceling Complexity**: Polymorphic parceling of interfaces requires a "factory" or "registry" in C++ to instantiate the correct concrete class when reading from a parcel.
- **Hide Annotations**: Many methods are `@hide` and `@UnsupportedAppUsage`, indicating they are intended for framework internal use.
