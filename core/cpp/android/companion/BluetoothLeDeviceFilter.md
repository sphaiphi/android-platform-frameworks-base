# BluetoothLeDeviceFilter - Reverse Engineering Documentation

## Executive Summary
`BluetoothLeDeviceFilter` is a criteria object for filtering Bluetooth Low Energy (BLE) devices. It extends the standard Android `ScanFilter` capabilities with additional raw data masking and a powerful renaming feature that allows dynamic display names based on advertisement data.

## Architecture Overview
This class implements `DeviceFilter<ScanResult>` and `Parcelable`. It wraps a `android.bluetooth.le.ScanFilter` and adds proprietary Companion Device Manager (CDM) filtering logic. It uses a `Builder` for construction.

## Detailed Functionality

### Extended Filtering
**Purpose**: To match BLE devices beyond what standard `ScanFilter` allows.
**Mechanism**:
1. Delegates primary matching to `ScanFilter.matches(scanResult)`.
2. Performs regex matching on the device name via `BluetoothDeviceFilterUtils.matchesName`.
3. Performs bitwise masked comparison on the raw advertisement bytes if `mRawDataFilter` is provided (using `BitUtils.maskedEquals`).

### Dynamic Renaming Logic
**Purpose**: To allow apps to customize how a device appears in the selection dialog based on its advertisement data.
**Algorithm**:
The `getDeviceDisplayName(ScanResult sr)` method:
1. If `mRenameBytesFrom >= 0`:
    - Extracts a range of bytes from the scan record.
    - Converts them to a hex string (handles Big/Little Endian via `mRenameBytesReverseOrder`).
    - Prepends `mRenamePrefix` and appends `mRenameSuffix`.
2. Else if `mRenameNameFrom >= 0`:
    - Extracts a substring from the advertised device name.
    - Applies prefix and suffix.
3. Otherwise: Returns the default display name.

### Hex Encoding
**Java-Specific Notes**: Uses `libcore.util.HexEncoding` for byte-to-hex conversion.

## Data Model
- `mScanFilter`: Standard BLE scan criteria.
- `mRawDataFilter` / `mRawDataFilterMask`: Bytes for raw packet matching.
- `mRenamePrefix` / `mRenameSuffix`: Strings for custom display names.
- `mRenameBytesFrom` / `mRenameBytesLength`: Byte indices for renaming.
- `mRenameNameFrom` / `mRenameNameLength`: Character indices for renaming.

## API Reference
- `matches(ScanResult)`: Combined filter predicate.
- `getDeviceDisplayName(ScanResult)`: Generates the customized name.
- `getMediumType()`: Returns `MEDIUM_TYPE_BLUETOOTH_LE` (1).

## Java-to-C++ Translation Guide
- **Renaming**: Use `std::stringstream` and `std::hex` or a native hex utility for formatting bytes.
- **Endianness**: Replicate the loop logic in `getDeviceDisplayName` to handle byte reversal for Little Endian inputs.
- **Data Types**: Use `std::vector<uint8_t>` for raw filters and masks.

## Implementation Risks
- **ScanRecord access**: Depends on `sr.getScanRecord().getBytes()`. In C++, ensure the BLE scan result provides access to the raw payload.
- **Index Safety**: Substring and byte range extraction must check bounds to avoid out-of-range exceptions.
- **Prefix Length Limit**: Enforced at 10 characters to prevent UI overflow.
