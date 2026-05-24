# DeviceId - Reverse Engineering Documentation

## Executive Summary
`DeviceId` is a final class that represents a unique identifier for a companion device, as managed by the companion app. It allows identification using either a custom application-provided string or a standard MAC address.

## Architecture Overview
This class is a `Parcelable` data object introduced to provide a more flexible identification scheme than just MAC addresses. It uses a `Builder` pattern for construction and enforces constraints on ID length.

## Detailed Functionality

### Identification Scheme
**Purpose**: To allow apps to use their own IDs (e.g., cloud-generated IDs) or hardware MAC addresses to track associations.
**Algorithm** (`isSameDevice`):
1. If both devices have non-null `customId`, compares them via string equality.
2. Else if both have non-null `macAddress`, compares them via `MacAddress.equals`.
3. Otherwise, returns false.

### Validation
- **Custom ID Limit**: Max 1024 characters.
- **Construction Requirement**: At least one of `customId` or `macAddress` must be provided.

## Data Model
- `mCustomId`: `String` - App-managed unique identifier.
- `mMacAddress`: `MacAddress` - Hardware hardware address.

## API Reference
- `getCustomId()`: Returns the app-provided ID.
- `getMacAddress()`: Returns the hardware address.
- `getMacAddressAsString()`: Returns the MAC in uppercase.

## Java-to-C++ Translation Guide
- **Strong Types**: Use `std::string` for the custom ID and a native `MacAddress` class.
- **Safety**: Use `std::optional` for the ID fields.
- **Pattern**: Replicate the `Builder` pattern to ensure the "at least one non-null" invariant is maintained.

## Implementation Risks
- **ID Collision**: If an app provides conflicting custom IDs across different MACs, the system's management logic might behave unexpectedly.
- **Disk Space**: The 1024 character limit is a mitigation for potential storage abuse by apps in the CDM persistent database.
