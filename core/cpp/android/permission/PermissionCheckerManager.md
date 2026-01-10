# PermissionCheckerManager - Reverse Engineering Documentation

## Executive Summary
`PermissionCheckerManager` is a manager class designed to facilitate permission checks, specifically bridging runtime permissions and AppOps. It serves as a wrapper around the `IPermissionChecker` service and provides local caching optimization for permission checks.

## Architecture Overview
- **Pattern**: Manager/Proxy with Caching.
- **Dependencies**: `IPermissionChecker`, `Context`, `PackageManager`, `AppOpsManager`.
- **Optimization**: Performs local checks for non-AppOp permissions to avoid IPC overhead.

## Detailed Functionality

### Permission Checking (`checkPermission`)
1.  **Optimization Check**: Checks if the permission maps to an AppOp code.
    -   If `AppOpsManager.permissionToOpCode(permission) == OP_NONE`: It's a non-runtime, non-op permission.
        -   **Local Check**: If `fromDatasource` is false, it calls `mContext.checkPermission`.
        -   If `fromDatasource` is true, it checks the permission against the *next* attribution source in the chain.
        -   Returns `PERMISSION_GRANTED` or `PERMISSION_HARD_DENIED`.
2.  **IPC Check**: If it is an AppOp permission, it delegates to `mService.checkPermission` (IPC to `IPermissionChecker`).

### AppOp Checking (`checkOp`)
Delegates directly to `mService.checkOp`.

### Data Delivery (`finishDataDelivery`)
Delegates directly to `mService.finishDataDelivery` to signal the end of data usage (for AppOps accounting).

## Data Model
-   **Permission Result Constants**:
    -   `PERMISSION_GRANTED` (0)
    -   `PERMISSION_SOFT_DENIED` (1): Runtime granted but AppOp denied/ignored.
    -   `PERMISSION_HARD_DENIED` (2): Permission denied.

## API Reference
-   `checkPermission(...)`: Validates attribution source chain and checks permission/AppOp.
-   `finishDataDelivery(...)`: Finishes an AppOp usage.
-   `checkOp(...)`: Checks/Notes an AppOp.

## Java-to-C++ Translation Guide

### Optimization Logic
The C++ implementation **must** replicate the optimization logic:
1.  Check if the permission has a corresponding AppOp.
2.  If not, check the permission locally using `checkPermission` on the context/package manager equivalent to avoid unnecessary IPC.

### IPC Interface
-   Map `IPermissionChecker` to the C++ AIDL generated interface.
-   `AttributionSourceState` in Java maps to `android::content::AttributionSourceState` in C++.

### C++ Type Equivalents
-   `Context` -> `android::content::Context` (if available) or `IPackageManager`/`IPermissionManager`.
-   `AttributionSourceState` -> `android::content::AttributionSourceState`.

## Implementation Risks
-   **Performance**: Failure to implement the local check optimization will result in excessive IPC calls for standard permissions.
-   **Attribution Chains**: Correctly traversing the `AttributionSource` chain (checking `next`) is critical for accurate permission attribution in the "from datasource" scenario.
