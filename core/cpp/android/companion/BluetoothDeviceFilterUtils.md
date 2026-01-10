# BluetoothDeviceFilterUtils - Reverse Engineering Documentation

## Executive Summary
`BluetoothDeviceFilterUtils` is a hidden utility class that provides shared logic for filtering and identifying Bluetooth and Wi-Fi devices. It handles string-to-regex conversion, hardware address matching, and bitmask-based UUID comparisons.

## Architecture Overview
This is a stateless utility class with private constructor and static methods. It is used by `BluetoothDeviceFilter`, `BluetoothLeDeviceFilter`, and `WifiDeviceFilter`.

## Detailed Functionality

### Name Matching
**Purpose**: Regex-based name validation for Bluetooth devices and Wi-Fi SSIDs.
**Algorithm**:
- For `BluetoothDevice`: Matches against `device.getName()`.
- For `ScanResult` (Wi-Fi): Matches against `device.SSID`.
- If the pattern is null, returns true.

### UUID Masked Comparison
**Purpose**: Checks if two UUIDs are equivalent when masked.
**Algorithm** (`uuidsMaskedEquals`):
1. Takes two 128-bit UUIDs and a mask UUID.
2. Performs bitwise `AND` between the mask and both UUIDs.
3. Compares the results for both the Least Significant Bits (LSB) and Most Significant Bits (MSB).
4. If mask is null, performs a direct equality check.

### Display Name Retrieval
**Purpose**: Provides a user-friendly name for a device.
- For Bluetooth: Returns `alias` if not empty, otherwise `address`.
- For Wi-Fi: Returns `SSID` if not empty, otherwise `BSSID`.

### MAC Address Extraction
**Purpose**: Polymorphic extraction of MAC addresses from various device types.
**Java-Specific Notes**: Uses `instanceof` to branch logic for `BluetoothDevice`, `ScanResult`, and `android.bluetooth.le.ScanResult`.

## API Reference (Static)
- `matchesAddress(String, BluetoothDevice)`: String equality check on address.
- `matchesServiceUuids(...)`: Iterates and checks multiple UUIDs using masks.
- `uuidsMaskedEquals(UUID, UUID, UUID)`: Core bitwise logic for partial UUID matches.
- `getDeviceMacAddress(Parcelable)`: Returns string representation of MAC.

## Java-to-C++ Translation Guide
- **UUID Logic**: Implement as a helper taking `uint64_t` pairs (MSB/LSB) or a custom 128-bit struct.
- **Polymorphism**: The `getDeviceMacAddress` method should be handled via method overloading or a `std::variant` visitor in C++.
- **Strings**: Ensure `MacAddress` string format (typically uppercase) is consistent with the rest of the framework.

## Implementation Risks
- **Regex compatibility**: Ensure C++ `std::regex` or the chosen regex engine matches Java's `java.util.regex.Pattern` semantics.
- **Endianness**: Masking logic on MSB/LSB assumes 64-bit segments. Ensure byte order is handled correctly if passing raw byte arrays.
