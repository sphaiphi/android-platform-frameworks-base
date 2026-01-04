# AssociationRequest - Reverse Engineering Documentation

## Executive Summary
`AssociationRequest` encapsulates the parameters for requesting a user to select and associate with a companion device. It supports filtering devices by medium (Bluetooth, BLE, Wi-Fi), specifying device profiles (e.g., "watch"), and configuring system behaviors like self-management or skipping role grants.

## Architecture Overview
The class implements `Parcelable` and uses a `Builder` pattern (extending `OneTimeUseBuilder`). It contains a list of `DeviceFilter` objects that define the criteria for device discovery.

## Detailed Functionality

### Device Profiles
The class defines several string constants for standardized device types:
- `DEVICE_PROFILE_WATCH`
- `DEVICE_PROFILE_GLASSES`
- `DEVICE_PROFILE_APP_STREAMING`
- `DEVICE_PROFILE_VIRTUAL_DEVICE`
- etc.
These profiles often trigger specific UI flows or permission grants in the system.

### Filtering Mechanism
**Purpose**: To limit the list of devices shown to the user.
**Mechanism**: A `List<DeviceFilter<?>>` is maintained. Each filter is specialized for a medium (e.g., `BluetoothDeviceFilter`).

### System-Populated Fields
Some fields are `@hide` and are intended to be set by the `CompanionDeviceManagerService` rather than the calling app:
- `mPackageName`
- `mUserId`
- `mDeviceProfilePrivilegesDescription`
- `mSkipPrompt`

### Logic: Builder Validation
- `setDisplayName`: Enforces a length limit of 1024 characters.
- `build()`: Ensures that if `mSelfManaged` is true, a `mDisplayName` MUST be provided.

## Data Model
- `mSingleDevice`: boolean - If true, discovery stops after finding one match.
- `mDeviceFilters`: List of `DeviceFilter`.
- `mDeviceProfile`: String - Role-based profile.
- `mSelfManaged`: boolean - App handles its own connection.
- `mForceConfirmation`: boolean - Collect explicit user consent even if not strictly required.
- `mCreationTime`: long - Timestamp of request creation.

## API Reference
- `isSelfManaged()`: Returns whether the app manages the connection.
- `getDeviceFilters()`: Returns the list of criteria for discovery.
- `isSingleDevice()`: Returns if scanning should stop after first match.

## Java-to-C++ Translation Guide
- **Pattern**: Maintain the `Builder` pattern. Use `std::vector<std::unique_ptr<DeviceFilter>>` or similar for polymorphic filters.
- **Strings**: Use `std::string` or `std::u16string`.
- **Validation**: Replicate the "one-time use" logic of the builder to prevent accidental modifications after build.

## Implementation Risks
- **Polymorphism in Parceling**: `writeParcelableList` and `readParcelableList` require careful handling in C++ to ensure the correct filter subclasses are instantiated.
- **Hidden State**: Ensure that system-populated fields are not exposed to public-facing C++ APIs if mimicking the Android SDK structure.
