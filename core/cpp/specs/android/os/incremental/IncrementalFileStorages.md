# IncrementalFileStorages - Reverse Engineering Documentation

## Executive Summary
`IncrementalFileStorages` manages the setup and lifecycle of file storages used during an incremental installation session. It orchestrates the creation of an `IncrementalStorage` instance (via `IncrementalManager`), binds it to the staging directory, adds APK files to it, and starts the data loading process. It also handles linking files from an inherited storage (if applicable) and cleaning up resources upon completion or failure.

## Architecture Overview
-   **Role**: Manager / Coordinator.
-   **Dependencies**:
    -   `IncrementalManager`: System service wrapper for creating/opening storages.
    -   `IncrementalStorage`: Represents the actual mounted Incremental FS.
    -   `DataLoaderParams`: Configuration for the data loader.
-   **Key Concepts**:
    -   **Default Storage**: The new storage created for this installation session.
    -   **Inherited Storage**: An existing storage from which files can be linked (deduplication).
    -   **Stage Dir**: The directory where the installation artifacts are staged.

## Detailed Functionality

### Initialization (`initialize`)
1.  Obtains `IncrementalManager` from system context.
2.  Creates an instance of `IncrementalFileStorages`.
    -   Checks if an `inheritedDir` is provided and is a valid incremental path.
    -   If so, opens it as `mInheritedStorage` and creates a **linked** storage for `mDefaultStorage`.
    -   Otherwise, creates a new `mDefaultStorage` using `dataLoaderParams`.
3.  Iterates through `addedFiles` (InstallationFileParcel).
    -   Adds APK files (`LOCATION_DATA_APP`) to the default storage using `makeFile`.
4.  Registers a progress callback if provided.
5.  Calls `startLoading` to kick off the data loader.

### File Operations
-   **`addApkFile`**: Creates a file record in the storage with metadata and signature. Does not write content immediately (handled by loader or `makeFile` with content).
-   **`makeFile`**: Creates a file with specific content (byte array). Used for small files or metadata.
-   **`makeLink`**: Creates a hard link from the inherited storage to the default storage. This is a crucial optimization for incremental updates, avoiding re-downloading unchanged files.

### Lifecycle Management
-   **`startLoading`**: Delegated to `mDefaultStorage`.
-   **`cleanUpAndMarkComplete`**: Unbinds the storage and notifies the service that installation is complete (allowing timeouts to be relaxed).
-   **`disallowReadLogs`**: Disables read logging (privacy/performance).

## Data Model
-   **Storage ID**: Integer ID identifying the storage in `IIncrementalService`.
-   **Paths**: Absolute paths are used for binding and file creation.

## API Reference
-   `initialize(...)`: Static factory method.
-   `makeFile(...)`, `makeLink(...)`: File manipulation.
-   `startLoading(...)`: Start data transfer.
-   `cleanUpAndMarkComplete()`: Finish session.

## Java-to-C++ Translation Guide
-   **Manager/Storage Interaction**: The logic heavily relies on `IncrementalManager` and `IncrementalStorage`, which are wrappers around the AIDL `IIncrementalService`.
-   **C++ Equivalent**: If implementing an installer in C++, interaction would be directly with `IIncrementalService` via Binder. The logic of "check inherited -> create linked OR create new" would need to be replicated.
-   **File System Operations**: Java uses `File` and `Path` utilities. C++ would use `std::filesystem` or POSIX `mkdir`/`link`/`open`.

## Implementation Risks
-   **Resource Leaks**: Ensure `cleanUp` is called on failure (try-catch blocks in Java).
-   **Bind Mounts**: Requires appropriate privileges (managed by `IncrementalService`).
-   **Path Validation**: Security risk if paths are not validated (though `IncrementalService` likely enforces isolation).