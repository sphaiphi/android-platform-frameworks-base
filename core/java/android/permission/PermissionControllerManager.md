# PermissionControllerManager - Reverse Engineering Documentation

## Executive Summary
`PermissionControllerManager` acts as the primary interface for system apps to communicate with the `PermissionController` app (the system component that handles permission UI and logic). It manages the connection to the remote service (`IPermissionController`) and provides asynchronous APIs for managing runtime permissions, backups, and app usage counts.

## Architecture Overview
- **Pattern**: Service Connector / Client-Side Proxy.
- **Service Binding**: Uses `ServiceConnector` to manage a bound connection to the `PermissionControllerService` implementation (found via `PackageManager`).
- **Threading**: Heavy use of `Executor` and `AndroidFuture` for asynchronous operations.
- **Caching**: Caches remote service connections per user and thread.

## Detailed Functionality

### Service Connection
-   Resolves the service intent `android.permission.PermissionControllerService`.
-   Binds to the service provided by the package defined in `PackageManager.getPermissionControllerPackageName()`.
-   Manages timeouts (`REQUEST_TIMEOUT_MILLIS`, `UNBIND_TIMEOUT_MILLIS`).

### Core Operations
1.  **Revoke Runtime Permissions**: Asks the controller to revoke permissions, potentially with a dry run.
2.  **Get/Restore Backup**: Handles streaming backup data via `ParcelFileDescriptor` pipes.
3.  **App Permission Queries**: Gets runtime permission info, counts apps with permissions, gets usage info.
4.  **Grant/Upgrade**: Triggers the default permission grant/upgrade logic.
5.  **Hibernation**: Queries hibernation eligibility and unused app counts.
6.  **Device Admin**: Sets grant states based on admin policy.

## Data Model
-   **Requests**: Permissions are often passed as `Map<String, List<String>>` (Package -> Permissions).
-   **Responses**: `RuntimePermissionPresentationInfo`, `RuntimePermissionUsageInfo`.
-   **Constants**: `REASON_MALWARE`, `REASON_INSTALLER_POLICY_VIOLATION`, `COUNT_ONLY_WHEN_GRANTED`, `HIBERNATION_ELIGIBILITY_*`.

## API Reference
(Selected Key Methods)
-   `revokeRuntimePermissions(...)`: Revoke permissions for multiple apps.
-   `getRuntimePermissionBackup(...)`: Get backup stream.
-   `stageAndApplyRuntimePermissionsBackup(...)`: Restore backup stream.
-   `getAppPermissions(...)`: Get permissions for a specific app.
-   `countPermissionApps(...)`: Count apps holding specific permissions.
-   `getPermissionUsages(...)`: Get recent permission usage.
-   `updateUserSensitiveForApp(...)`: Update sensitive flags.

## Java-to-C++ Translation Guide

### Async Model
Java uses `AndroidFuture` and `CompletableFuture` patterns. C++ implementation should likely use `std::future` or a callback mechanism, potentially integrating with `libbinder`'s async capabilities.

### Service Connector
The `ServiceConnector` logic (auto-binding, unbinding, retrying) is complex. In C++, if this runs in a long-lived process (like system_server), a similar service watcher/binder caching mechanism is needed. If it runs in a short-lived command, standard `bindService` might suffice.

### IPC
-   Use `IPermissionController` AIDL.
-   Handle `ParcelFileDescriptor` for backup streams carefully (file descriptor passing).

## Implementation Risks
-   **Service Lifecycle**: The Permission Controller app can update or crash. The manager must handle reconnection gracefully.
-   **Data Streams**: Backup/Restore involves piping data. Ensure pipe closure and error handling are robust in C++ to avoid leaks or hangs.
