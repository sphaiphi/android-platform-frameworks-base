# PermissionManagerInternal - Reverse Engineering Documentation

## Executive Summary
`PermissionManagerInternal` is a local interface used for communication between system server components. It is **not** exposed to apps or via Binder. It provides privileged access to permission storage and state management mechanisms that are too sensitive or implementation-specific for the public AIDL interface.

## Architecture Overview
- **Pattern**: Internal Local Interface.
- **Scope**: System Server only (in-process).
- **Usage**: Used by `PackageManagerService` and other core system services.

## Detailed Functionality
1.  **Backup**: `backupRuntimePermissions` retrieves the runtime permission state as a generic byte blob.
2.  **Restore**: `restoreRuntimePermissions` applies a previously backed-up blob.
3.  **Delayed Restore**: `restoreDelayedRuntimePermissions` attempts to apply permission grants for a package that might have been missing during the initial restore.

## Data Model
-   **Blob**: The backup format is an opaque `byte[]`, implementation-defined by the Permission Manager service.

## API Reference
-   `backupRuntimePermissions(int userId)`: Returns `byte[]`.
-   `restoreRuntimePermissions(byte[] backup, int userId)`: Void.
-   `restoreDelayedRuntimePermissions(String packageName, int userId)`: Void.

## Java-to-C++ Translation Guide
*Note: This interface is likely implemented by the Java system server services. Direct C++ translation is only relevant if moving the Permission Manager implementation itself to C++.*

If calling this from C++ within the system server (e.g., if parts of PM are native), you would need a native local service interface, likely via `LocalServices` mechanism if one exists for native, or JNI calls to the Java implementation.

## Implementation Risks
-   **Opaque Blob**: The format of the backup blob is internal. If C++ code needs to parse it, the format must be strictly documented or shared definitions used.
