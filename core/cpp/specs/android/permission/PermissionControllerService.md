# PermissionControllerService - Reverse Engineering Documentation

## Executive Summary
`PermissionControllerService` is an abstract base class that defines the contract for the system's Permission Controller application. It exposes the `IPermissionController` AIDL interface and enforces permission checks on callers, ensuring only authorized system components can invoke its methods.

## Architecture Overview
- **Pattern**: Service Base Class (Abstract).
- **Role**: Server-side implementation stub for the Permission Controller.
- **Security**: Enforces `Manifest.permission` checks on all incoming binder calls.

## Detailed Functionality

### Method Enforcement
The class implements `IPermissionController.Stub` and wraps abstract `on...` methods. Each wrapper:
1.  **Validates Arguments**: Checks for nulls, empty strings, etc.
2.  **Enforces Permissions**: Calls `enforceSomePermissionsGrantedToCaller` to verify the caller holds the necessary permissions (e.g., `REVOKE_RUNTIME_PERMISSIONS`, `GET_RUNTIME_PERMISSIONS`).
3.  **Delegates**: Calls the abstract `on...` method which the concrete implementation (the App) must provide.

### Key Operations
-   **Runtime Permissions**: `onRevokeRuntimePermissions`, `onGrantOrUpgradeDefaultRuntimePermissions`.
-   **Backup/Restore**: `onGetRuntimePermissionsBackup`, `onStageAndApplyRuntimePermissionsBackup`.
-   **Information**: `onGetAppPermissions`, `onCountPermissionApps`, `onGetPermissionUsages`.
-   **One-Time Permissions**: `onOneTimePermissionSessionTimeout`.

## Data Model
-   **Service Interface**: `android.permission.PermissionControllerService`.
-   **Callbacks**: Uses `Consumer<T>`, `Runnable`, and `IntConsumer` to return results asynchronously to the binder thread.

## API Reference
(Abstract methods to be implemented by subclass)
-   `onRevokeRuntimePermissions(...)`
-   `onGetRuntimePermissionsBackup(...)`
-   `onStageAndApplyRuntimePermissionsBackup(...)`
-   `onGetAppPermissions(...)`
-   `onRevokeRuntimePermission(...)`
-   `onCountPermissionApps(...)`
-   `onGetPermissionUsages(...)`
-   `onGrantOrUpgradeDefaultRuntimePermissions(...)`
-   `onSetRuntimePermissionGrantStateByDeviceAdmin(...)`

## Java-to-C++ Translation Guide
*Note: This is a base class for a Java App (PermissionController). It is unlikely to be fully translated to C++ unless the Permission Controller logic itself is being moved to native code.*

If implementing a C++ service that mimics this:
1.  **Binder Stub**: Inherit from `BnPermissionController`.
2.  **Permission Checks**: Implement `checkCallingPermission` logic using `PermissionManager` or `ActivityManager`.
3.  **Argument Validation**: Replicate the `Preconditions` checks.

## Implementation Risks
-   **Security**: The core responsibility of this class is checking permissions before delegation. Missing a check exposes the Permission Controller logic to unauthorized apps.
-   **Compatibility**: Deprecated methods (`onRestoreRuntimePermissionsBackup`) must still be supported or properly redirected.
