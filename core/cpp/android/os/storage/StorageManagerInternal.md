# StorageManagerInternal - Reverse Engineering Documentation

## Executive Summary
`StorageManagerInternal` is a local system service interface exposed by `StorageManagerService` for use *only* by other system services (like `PackageManagerService`, `UserManagerService`) running within the same process (`system_server`). It exposes privileged, low-level operations not suitable for the public `StorageManager` API.

## Architecture Overview
-   **Pattern**: Local Service Interface (SystemService.Target).
-   **Scope**: In-process communication within System Server.

## Key Methods
-   **`getExternalStorageMountMode(uid, pkg)`**: Determines if an app gets full/read/write/default view of external storage.
-   **`prepareUserStorageForMove`**: Prepares destination directories for data migration.
-   **`onAppOpsChanged`**: Notifies storage layer to remount/update views when permissions change.
-   **`enableFsverity`**: Proxy to installer for Verity setup.
-   **`freeCache`**: Request to free space (blocks until done).

## Java-to-C++ Translation Guide
-   **Not Applicable**: This is a Java-only internal interface for the System Server architecture. C++ components typically interact via the Binder `IStorageManager` or `vold` sockets.
