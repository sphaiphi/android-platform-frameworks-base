# WifiDeviceFilter - Reverse Engineering Documentation

## Executive Summary
`WifiDeviceFilter` defines criteria for filtering Wi-Fi devices during the companion discovery process. It supports matching based on the SSID (via regex pattern) and the BSSID (with bitmasking support for partial address matches).

## Architecture Overview
This class implements `DeviceFilter<ScanResult>` and `Parcelable`. It uses `BluetoothDeviceFilterUtils` for shared name matching logic and relies on the `android.net.MacAddress` class for BSSID validation.

## Detailed Functionality

### Matching Logic
**Purpose**: To determine if a Wi-Fi `ScanResult` meet the association criteria.
**Algorithm**:
The `matches(ScanResult device)` method returns true if:
1. `BluetoothDeviceFilterUtils.matchesName(mNamePattern, device)` is true (matches SSID).
2. AND either `mBssid` is null, or `MacAddress.fromString(device.BSSID).matches(mBssid, mBssidMask)` is true.

### BSSID Masking
**Purpose**: To allow matching ranges of BSSIDs (e.g., matching all devices from a specific manufacturer/OUI).
**Mechanism**:
- `mBssid`: The target BSSID.
- `mBssidMask`: A bitmask where `1` indicates a bit that must match. Default is `BROADCAST_ADDRESS` (all ones, exact match).

### Medium Type
Identifies itself as `MEDIUM_TYPE_WIFI` (2).

## Data Model
- `mNamePattern`: `Pattern` - Regex for SSID.
- `mBssid`: `MacAddress` - Target BSSID.
- `mBssidMask`: `MacAddress` - Bitmask for BSSID comparison.

## API Reference
- `matches(ScanResult)`: Predicate for filtering.
- `getDeviceDisplayName(ScanResult)`: Returns SSID or BSSID.

## Java-to-C++ Translation Guide
- **Regex**: Use `std::regex`.
- **MAC Logic**: Port the `matches(MacAddress, MacAddress)` bitwise logic from Android's `MacAddress` class if not already available in the C++ stack.
- **Serialization**: Note the custom `Parcelling` for the `Pattern` object. Reconstruct using a regex engine factory.

## Implementation Risks
- **ScanResult Parsing**: Note that `device.BSSID` is a string in Java. Converting it to a `MacAddress` object for every match call can be expensive. Consider caching or pre-parsing in the C++ layer.
- **Validation**: The builder enforces `NonNull` on `mBssidMask` but allows `null` for `mBssid`.
