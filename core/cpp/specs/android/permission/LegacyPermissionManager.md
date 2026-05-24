# LegacyPermissionManager - Reverse Engineering Documentation

## Executive Summary
`LegacyPermissionManager` is a system service wrapper that provides access to legacy permission management features. It primarily handles checks for device identifier access, phone number access, and manages default permissions for carrier, LUI, IMS, and telephony data service applications.

## Architecture Overview
- **Pattern**: Proxy/Manager.
- **IPC**: Uses `ILegacyPermissionManager` AIDL interface to communicate with the `legacy_permission` system service.
- **Context**: Registered as `Context.LEGACY_PERMISSION_SERVICE`.

## Detailed Functionality

### Permission Checks
1.  **Device Identifier Access**: Checks if a package can access device identifiers (like IMEI/MEID).
2.  **Phone Number Access**: Checks if a package can read the device's phone number.

### Default Permission Grants
Provides methods to grant or revoke default permissions for specific types of system-related apps:
-   **LUI Apps**: Local Usage Interface apps.
-   **IMS Services**: IP Multimedia Subsystem services.
-   **Telephony Data Services**: Services handling telephony data.
-   **Carrier Apps**: Apps privileged by the carrier.
-   **Carrier Service App**: A specific carrier service app.

These methods generally dispatch an asynchronous task (via an `Executor`) to call the system server and then invoke a callback with the result.

## API Reference

### Checks
-   `checkDeviceIdentifierAccess(String packageName, String message, String callingFeatureId, int pid, int uid)`: Returns `int` (Permission State).
-   `checkPhoneNumberAccess(String packageName, String message, String callingFeatureId, int pid, int uid)`: Returns `int` (Permission State or AppOps Mode).

### Management (Async)
-   `grantDefaultPermissionsToLuiApp(...)`
-   `revokeDefaultPermissionsFromLuiApps(...)`
-   `grantDefaultPermissionsToEnabledImsServices(...)`
-   `grantDefaultPermissionsToEnabledTelephonyDataServices(...)`
-   `revokeDefaultPermissionsFromDisabledTelephonyDataServices(...)`
-   `grantDefaultPermissionsToEnabledCarrierApps(...)`
-   `grantDefaultPermissionsToCarrierServiceApp(...)`

## Java-to-C++ Translation Guide

### Service Retrieval
In C++, use `defaultServiceManager()->getService(String16("legacy_permission"))` to get the `IBinder`, then cast to `ILegacyPermissionManager`.

### Method Mapping
Most methods map 1:1 to the `ILegacyPermissionManager` AIDL methods.
-   **Exception Handling**: Java catches `RemoteException` and rethrows as `RuntimeException`. C++ methods return `binder::Status` which should be checked.
-   **Callbacks**: The Java API uses `Executor` and `Consumer<Boolean>`. C++ clients calling the AIDL directly will block or need to implement their own async wrapper if strictly required, though typically NDK clients might call these synchronously.

## Data Model
Relies on standard types (`String`, `int`, `String[]`) and `UserHandle` (which maps to `int userId` in AIDL).

## Implementation Risks
-   **Binder Stability**: Ensure the `legacy_permission` service is available before calling.
-   **Concurrency**: The Java implementation handles threading for callbacks. C++ implementations accessing the binder directly will be blocking unless offloaded.
