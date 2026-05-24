# PermissionManager - Reverse Engineering Documentation

## Executive Summary
`PermissionManager` is the central system-level service interface for accessing and managing permissions in Android. It serves as the primary entry point for apps and system components to check, grant, revoke, and query permissions. It abstracts the underlying IPC to the `permissionmgr` service and provides higher-level logic for attribution, caching, and compatibility (e.g., split permissions).

## Architecture Overview
- **Pattern**: System Service Manager / Proxy.
- **IPC**: Wraps `IPermissionManager` (binder interface).
- **Dependencies**: `Context`, `PackageManager`, `LegacyPermissionManager`, `AppOpsManager`.
- **Caching**: Uses `PropertyInvalidatedCache` to cache permission checks and request states locally to reduce IPC traffic.

## Detailed Functionality

### Permission Checking
Provides a nuanced set of permission check APIs depending on the stage of data access:
1.  **`checkPermissionForDataDelivery`**: Used when data is *actually* being delivered. Checks permission and notes the AppOp.
2.  **`checkPermissionForStartDataDelivery`**: Like above, but starts the AppOp (requires `finishDataDelivery` later).
3.  **`checkPermissionForPreflight`**: Checks if an app *could* have access (e.g., before binding), without noting usage.
4.  **`checkPermissionForDataDeliveryFromDataSource`**: Used by data sources (like location providers) to check on behalf of a client.

### Permission Management
-   **Runtime Permissions**: `grantRuntimePermission`, `revokeRuntimePermission`.
-   **Flags**: `getPermissionFlags`, `updatePermissionFlags` (manages user set, system fixed, policy fixed states).
-   **Split Permissions**: Handles backward compatibility where one old permission maps to multiple new ones (e.g., Location -> Background Location).

### Attribution Source
-   **Registration**: `registerAttributionSource` allows apps to register their identity tokens with the system for secure blaming.
-   **Validation**: `isRegisteredAttributionSource`.

### Caching
-   **`sPermissionCache`**: Caches `checkPermission` results keyed by `PermissionQuery` (permission, pid, uid, deviceId).
-   **Invalidation**: Listens to system property changes (`package_info`) to invalidate caches when permissions change.

## Data Model
-   **Result Constants**:
    -   `PERMISSION_GRANTED` (0)
    -   `PERMISSION_SOFT_DENIED` (1): Granted but AppOp denied (silent failure).
    -   `PERMISSION_HARD_DENIED` (2): Fully denied.
-   **SplitPermissionInfo**: Maps legacy permissions to new granular permissions.

## API Reference
(Selected Key Methods)
-   `checkPermissionForDataDelivery(...)`: Secure check + Op note.
-   `grantRuntimePermission(...)`: Grant permission.
-   `revokeRuntimePermission(...)`: Revoke permission.
-   `getPermissionFlags(...)`: Get state flags.
-   `registerAttributionSource(...)`: Register identity.
-   `getSplitPermissions()`: Get compatibility mappings.
-   `startOneTimePermissionSession(...)`: Start session for temporary permissions.

## Java-to-C++ Translation Guide

### Caching Logic
The `PropertyInvalidatedCache` is critical for performance. In C++, this must be implemented using `libbinder`'s caching mechanisms or a custom map that invalidates based on the `package_info` system property.
-   **Cache Key**: `(permission, pid, uid, deviceId)`.
-   **Invalidation**: Watch `sys.package_info` (or equivalent).

### IPC
-   Use `IPermissionManager` AIDL.
-   `AttributionSource` serialization is complex; ensure the C++ `AttributionSourceState` matches the Java structure.

### Split Permissions
The split permission logic (mapping one permission to many) is client-side logic in `PermissionManager`. This logic must be replicated in C++ if C++ components need to handle legacy apps correctly.

## Implementation Risks
-   **Cache Coherency**: If the C++ cache doesn't invalidate correctly, permission updates (grants/revocations) won't be seen immediately, leading to security issues or app crashes.
-   **Attribution Chains**: Correctly handling the `AttributionSource` chain in C++ is essential for privacy accounting.
