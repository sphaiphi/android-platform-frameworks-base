# PermissionChecker - Reverse Engineering Documentation

## Executive Summary
`PermissionChecker` provides APIs to check permissions, verifying both the runtime permission (e.g., `Manifest.permission.CAMERA`) and the associated App Op (e.g., `AppOpsManager.OP_CAMERA`). It handles the complexities of legacy apps (pre-M) where permissions are granted but ops might be revoked.

## Architecture Overview
- **Type:** Utility class (Static methods).
- **Dependency:** `PermissionCheckerManager` (System Service).

## Detailed Functionality

### `checkPermissionForDataDelivery`
**Purpose**: Checks permission at the point of data delivery. records access (notes the op).
**Algorithm**: Calls `PermissionCheckerManager.checkPermission` with `startDataDelivery=false`, `forDataDelivery=true`.

### `checkPermissionForPreflight`
**Purpose**: Checks permission for "pre-flight" (before data delivery, e.g., binding). Does not record access (checks the op silently).
**Algorithm**: Calls `PermissionCheckerManager.checkPermission` with `forDataDelivery=false`.

### `checkSelfPermission...` / `checkCallingPermission...`
**Purpose**: Helpers for checking self or IPC caller.

## Constants
- `PERMISSION_GRANTED`
- `PERMISSION_SOFT_DENIED` (Permission granted, but App Op denied - e.g., legacy app with op disabled).
- `PERMISSION_HARD_DENIED`.

## API Reference
- `public static int checkPermissionForDataDelivery(...)`
- `public static int checkPermissionForPreflight(...)`

## Java-to-C++ Translation Guide
- **Service Call**: Wraps calls to `IPermissionChecker` (via `PermissionCheckerManager` in Java, likely direct Binder in C++).

## Implementation Risks
- **Soft Denials**: Clients must correctly handle `PERMISSION_SOFT_DENIED` (usually treat as denial, but maybe with different UI feedback or fallback).