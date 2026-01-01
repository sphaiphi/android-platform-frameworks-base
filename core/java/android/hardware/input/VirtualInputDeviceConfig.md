# VirtualInputDeviceConfig - Reverse Engineering Documentation

## Executive Summary
`VirtualInputDeviceConfig` is the abstract base class for configuration data of any virtual input device.

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder Pattern**: Abstract builder with recursive generic type for chaining.

## Detailed Functionality
- **Fields**:
  - `mVendorId`: USB Vendor ID.
  - `mProductId`: USB Product ID.
  - `mAssociatedDisplayId`: Display to target.
  - `mInputDeviceName`: Name string.
- **Validation**: Name length check (max 80 bytes for uinput). Display ID check.

## Java-to-C++ Translation Guide
- Base struct/class.
- Validation logic should be replicated.

## Implementation Risks
- `DEVICE_NAME_MAX_LENGTH` limit (80 bytes) is a hard kernel limit (uinput).
