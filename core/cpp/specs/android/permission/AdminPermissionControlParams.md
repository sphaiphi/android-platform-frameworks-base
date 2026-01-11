# AdminPermissionControlParams - Reverse Engineering Documentation

## Executive Summary
`AdminPermissionControlParams` is a data class (Parcelable) used to encapsulate parameters for an administrator's request to control a specific permission for a specific application. It is primarily used by the `PermissionController`'s `setRuntimePermissionGrantStateByDeviceAdmin` method.

## Architecture Overview
- **Type**: Data Transfer Object (DTO) / Parcelable.
- **Package**: `android.permission`.
- **Role**: Carries data between the Device Policy Manager (admin) and the Permission Controller system.

## Detailed Functionality
The class is immutable and holds the following information:
1.  **Grantee Package**: The package name to which the permission grant state applies.
2.  **Permission**: The name of the permission being controlled.
3.  **Grant State**: The desired state (Granted, Denied, or Default).
4.  **Sensor Permission Grant**: A boolean indicating if the admin is allowed to grant sensor-related permissions.

It performs validation in the constructor to ensure package names and permissions are not empty and that the grant state is valid.

## Data Model
### `AdminPermissionControlParams`
| Field | Type | Description |
| :--- | :--- | :--- |
| `mGranteePackageName` | `String` | The package name of the app receiving the permission state change. |
| `mPermission` | `String` | The name of the permission (e.g., `android.permission.CAMERA`). |
| `mGrantState` | `int` | The grant state constant (GRANTED=1, DENIED=2, DEFAULT=0). |
| `mCanAdminGrantSensorsPermissions` | `boolean` | Whether the admin can control sensor permissions. |

## API Reference

### Constructor
```java
public AdminPermissionControlParams(String granteePackageName, String permission, int grantState, boolean canAdminGrantSensorsPermissions)
```
- **Preconditions**: `granteePackageName` and `permission` must not be empty. `grantState` must be one of `PERMISSION_GRANT_STATE_GRANTED`, `PERMISSION_GRANT_STATE_DENIED`, or `PERMISSION_GRANT_STATE_DEFAULT`.

### Getters
- `getGranteePackageName()`: Returns `String`.
- `getPermission()`: Returns `String`.
- `getGrantState()`: Returns `int`.
- `canAdminGrantSensorsPermissions()`: Returns `boolean`.

## Java-to-C++ Translation Guide

### Data Structure
Map this to a C++ `struct` or `class` with equivalent fields. Since it's Parcelable, it likely needs a corresponding AIDL definition or manual `Parcel` serialization logic in C++.

```cpp
// C++ Equivalent Draft
struct AdminPermissionControlParams {
    std::string granteePackageName;
    std::string permission;
    int grantState; // Enum matching DevicePolicyManager constants
    bool canAdminGrantSensorsPermissions;
    
    // Serialization logic needed for Parcel
    status_t writeToParcel(Parcel* parcel) const;
    status_t readFromParcel(const Parcel& parcel);
};
```

### Validation
Ensure the C++ constructor or factory method performs the same validation checks (non-empty strings, valid enum values).

## Test Cases & Validation
1.  **Serialization**: Verify that an object written to a Parcel in C++ can be read back correctly.
2.  **Validation**: Test that invalid grant states or empty strings cause the creation to fail (if factories are used) or are handled gracefully.

## Implementation Risks
- **Parcel Compatibility**: Ensure the order of writing fields matches exactly with the Java `writeToParcel` method: `String`, `String`, `int`, `boolean`.
