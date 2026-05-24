# StorageManager - Reverse Engineering Documentation

## Executive Summary
`StorageManager` is the primary system service client for managing storage devices, volumes, and OBBs. It communicates with `StorageManagerService` (and indirectly `vold`) to perform operations like mounting/unmounting, formatting, partitioning, and querying storage state. It also provides helper methods for path resolution and permission checks.

## Architecture Overview
-   **Pattern**: System Service Client / Manager.
-   **IPC**: Wraps `IStorageManager` (Binder interface).
-   **Components**:
    -   **OBBs**: Manages Opaque Binary Blobs via `mountObb` / `unmountObb`.
    -   **Volumes**: Queries `StorageVolume` list, manages volume state.
    -   **Listeners**: Registers `StorageEventListener` for state changes.
    -   **Quota/Cache**: Manages cache quotas via `getCacheQuotaBytes`.

## Key Functionality

### Volume Management
-   **`getVolumeList`**: Retrieves list of `StorageVolume`s. Uses `PropertyInvalidatedCache` for performance.
-   **`getStorageVolumes`**: Returns shared/external volumes available to the user.
-   **`getPrimaryStorageVolume`**: Returns the primary shared volume.

### OBB Support
-   **`mountObb`**: Asynchronously mounts an OBB file. Uses a `nonce` to correlate the request with the `IObbActionListener` callback.
-   **`isObbMounted`**, **`getMountedObbPath`**: Query status.

### File/Path Resolution
-   **`getUuidForPath(File)`**: Resolves a file path to its volume UUID. Used for quota attribution.
-   **`getStorageVolume(File)`**: Reverse lookup from path to Volume object.

### Encryption & User Storage
-   **`unlockCeStorage`**, **`prepareUserStorage`**: Methods called by `UserManagerService` during user lifecycle to manage FBE (File-Based Encryption) keys and directories.

### Quota & Cache
-   **`getStorageCacheBytes`**: Calculates recommended cache size based on device storage ("Smart Storage").
-   **`allocateBytes`**: Requests space allocation (potentially triggering cache clearing).

## Data Model
-   **States**: Media states (Mounted, Unmounted, Ejecting, etc.) mirroring `Environment` states.
-   **Flags**: `FLAG_STORAGE_DE`, `FLAG_STORAGE_CE` (Encryption awareness).

## Java-to-C++ Translation Guide
-   **Binder**: This class is a wrapper. C++ clients should use `IStorageManager` directly via `ServiceManager`.
-   **Logic Replication**:
    -   **Cache Logic**: The `computeStorageCacheBytes` algorithm (linear interpolation based on thresholds) might need replication if logic moves to native.
    -   **Path Resolution**: `getUuidForPath` logic (canonicalizing paths and checking against volume mount points) is critical for matching file descriptors to volumes.

## Implementation Risks
-   **Concurrency**: Uses `synchronized` on `mDelegates`.
-   **Cache Invalidation**: `sVolumeListCache` must be invalidated when volume state changes (handled by `StorageManagerService`).
