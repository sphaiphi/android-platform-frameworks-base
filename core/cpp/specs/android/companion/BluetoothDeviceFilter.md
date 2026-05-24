# BluetoothDeviceFilter - Reverse Engineering Documentation

## Executive Summary
`BluetoothDeviceFilter` provides criteria for filtering Classic Bluetooth (non-LE) devices during the discovery process. It allows matching based on device name (regex), MAC address, and supported Service UUIDs (with optional bitmasking).

## Architecture Overview
This class implements `DeviceFilter<BluetoothDevice>` and `Parcelable`. It leverages utility methods from `BluetoothDeviceFilterUtils` for the actual matching logic and string/pattern conversions.

## Detailed Functionality

### Matching Logic
**Purpose**: To determine if a `BluetoothDevice` meets the specified criteria.
**Algorithm**:
The `matches(BluetoothDevice device)` method returns true only if ALL specified criteria are met:
1. `matchesAddress(mAddress, device)`: Exact string match on hardware address.
2. `matchesServiceUuids(mServiceUuids, mServiceUuidMasks, device)`: Checks if any of the device's advertised UUIDs match the target UUIDs under the provided masks.
3. `matchesName(getNamePattern(), device)`: Regex match against the device's name.

### Service UUID Filtering
- `mServiceUuids`: List of target UUIDs to look for.
- `mServiceUuidMasks`: Optional masks applied to the device's UUIDs before comparison. This allows filtering for specific bits within a UUID.

### Medium Type
Identifies itself as `MEDIUM_TYPE_BLUETOOTH` (0).

## Data Model
- `mNamePattern`: `Pattern` (Regex) for the device name.
- `mAddress`: `String` for the MAC address.
- `mServiceUuids`: `List<ParcelUuid>`.
- `mServiceUuidMasks`: `List<ParcelUuid>`.

## API Reference
- `matches(BluetoothDevice device)`: Core matching predicate.
- `getDeviceDisplayName(BluetoothDevice device)`: Delegates to `BluetoothDeviceFilterUtils.getDeviceDisplayNameInternal`.

## Java-to-C++ Translation Guide
- **Regex**: Use `std::regex`. Note that Java's `Pattern` behavior should be matched (e.g., case sensitivity, partial matches).
- **UUIDs**: Use a native UUID structure (e.g., `uint8_t[16]` or a dedicated class).
- **Lists**: `std::vector<ParcelUuid>`.
- **Logic**: Port `BluetoothDeviceFilterUtils` first, as this class depends heavily on it.

## Implementation Risks
- **Pattern Serialization**: Java `Pattern` objects are not directly parcelable. This class converts them to strings during parceling. Ensure the C++ side can reconstruct the regex correctly.
- **UUID Masking**: Bitwise logic for masking 128-bit UUIDs must be handled carefully to avoid endianness issues.
