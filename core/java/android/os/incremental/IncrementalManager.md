# IncrementalManager - Reverse Engineering Documentation

## Executive Summary
`IncrementalManager` is the system service client for `IIncrementalService`. It provides high-level APIs to open, create, and manage Incremental File System (IncFS) storages. It also exposes utility methods to check feature support, link code paths, and retrieve metrics.

## Architecture Overview
-   **Pattern**: System Service Wrapper / Manager.
-   **Service**: `IIncrementalService` (Binder).
-   **Native Integration**: Uses JNI (`native...` methods) for direct file system checks (is path incremental, get signature).

## Detailed Functionality

### Storage Management
-   **`createStorage`**: Calls `mService.createStorage` or `createLinkedStorage`. Wraps the returned ID in an `IncrementalStorage` object.
    -   *Note*: When creating linked storage, it preserves the file mode of the target directory using `Os.chmod`.
-   **`openStorage`**: Calls `mService.openStorage` using the path.

### Linking Code Paths (`linkCodePath`)
This is a complex operation used during app installation/update.
1.  Opens the source storage (`apkStorage`).
2.  Creates a *new* linked storage at the target location (`linkedApkStorage`).
3.  Recursively walks the directory tree of the source (`linkFiles`).
    -   Replicates directory structure (`makeDirectory`).
    -   Creates hard links for files (`makeLink`).
4.  On failure, unbinds the target.

### Feature Support
-   **`isFeatureEnabled`**: Checks native support.
-   **`getVersion`**: Returns IncFS version (1 or 2). V2 adds Per-UID timeouts and fs-verity.
-   **`isAllowed`**: Checks global property `incremental.allowed`.

### Progress & Metrics
-   **`registerLoadingProgressCallback`**: Manages a `RemoteCallbackList` of listeners via `LoadingProgressCallbacks` inner class. This bridges the `IStorageLoadingProgressListener` (per-storage) to `IPackageLoadingProgressCallback` (per-package).
-   **`getMetrics`**: Retrieves `PersistableBundle` metrics for a path.

## Data Model
-   **Create Modes**: Flags defined in `CreateMode` annotation (Temporary/Permanent Bind, Create/Open).

## API Reference
-   `createStorage(...)`
-   `openStorage(String path)`
-   `linkCodePath(File, File)`
-   `isIncrementalPath(String)`: Static check.
-   `unsafeGetFileSignature(String)`: Native signature retrieval.

## Java-to-C++ Translation Guide
-   **Binder Interface**: `IIncrementalService` is the source of truth.
-   **JNI Methods**: The native methods (`nativeIsIncrementalPath`, etc.) in `android_os_incremental_IncrementalManager.cpp` (implied location) likely use `libincfs`.
-   **Recursive Linking**: The `linkFiles` logic using `Files.walkFileTree` needs a C++ equivalent (e.g., `fts` or `std::filesystem::recursive_directory_iterator`).

## Implementation Risks
-   **Permissions**: Creating storages requires specific system permissions.
-   **Mount Lifecycle**: Managing bind mounts (temporary vs permanent) is critical to avoid stale mounts or data loss.