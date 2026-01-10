# IncrementalStorage - Reverse Engineering Documentation

## Executive Summary
`IncrementalStorage` represents a handle to an open Incremental File System storage instance. It provides operations to manipulate the file system structure (files, directories, links, binds) and query its status (loading progress, health). It acts as a client proxy to `IIncrementalService` for a specific `storageId`.

## Architecture Overview
-   **Pattern**: Proxy / Handle.
-   **State**: Holds `storageId` and `IIncrementalService` reference.
-   **Operations**: Most methods directly map to AIDL calls on the service, passing `mId` as the first argument.

## Detailed Functionality

### Bind Mounts
-   **`bind` / `bindPermanent`**: Create bind mounts from the storage to other locations. Supports separate flags for temporary (cleared on reboot) vs permanent.
-   **`unBind`**: Removes a bind mount.

### File System Structure
-   **`makeDirectory` / `makeDirectories`**: Create dirs.
-   **`makeFile`**: Creates a file.
    -   Validates V4 Signature using `V4Signature.readFrom`.
    -   Converts UUID to bytes.
    -   Constructs `IncrementalNewFileParams` and calls service.
-   **`makeFileFromRange`**: "Clones" data from another file in the same storage (deduplication).
-   **`makeLink` / `unlink`**: Hard link management.
-   **`moveDir`**: Implemented as `makeBindMount` (permanent) followed by `deleteBindMount` (old path). **Note**: This is essentially a "rename" for mount points.

### Status & Loading
-   **`isFileFullyLoaded` / `isFullyLoaded`**: Check saturation.
-   **`getLoadingProgress`**: Returns float [0, 1].
-   **`startLoading`**: Initiates the DataLoader.

### Metadata
-   **`getFileMetadata`**: Retrieves raw metadata bytes by path or UUID.

## API Reference
-   `makeFile`, `makeDirectory`, `makeLink`
-   `bind`, `unBind`
-   `startLoading`
-   `getLoadingProgress`

## Java-to-C++ Translation Guide
-   **Direct Mapping**: This class is a thin wrapper. C++ code can call `IIncrementalService` methods directly with the storage ID.
-   **UUID Handling**: Java `UUID` splits into two `long`s. The service expects a 16-byte array. `idToBytes` does this conversion (Big Endian logic: MSB then LSB).
-   **V4 Signature**: The `validateV4Signature` helper logic needs to be present in C++ (likely `libincfs` has utilities for this).

## Implementation Risks
-   **UUID Endianness**: Ensure byte order matches when converting UUIDs.
-   **Error Handling**: Methods throw `IOException` wrapping the errno returned by the service (negated). C++ should handle negative return codes as errors.