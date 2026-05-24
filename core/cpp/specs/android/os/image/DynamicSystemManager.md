# DynamicSystemManager - Reverse Engineering Documentation

## Executive Summary
`DynamicSystemManager` is the system service wrapper for managing Dynamic System Updates (DSU). It provides low-level control over the installation, enabling, and removal of temporary system images (GSIs). It interacts with the `IDynamicSystemService` Binder interface (which likely wraps the native `gsi` service). It supports streaming installation data via shared memory (Ashmem).

## Architecture Overview
-   **Pattern**: System Service Wrapper / Proxy
-   **Underlying Service**: `IDynamicSystemService` (AIDL)
-   **Key Concept**: **Session**. An inner class representing an active installation session, allowing stateful operations like streaming data.
-   **Data Flow**:
    -   Control path: `DynamicSystemManager` -> `IDynamicSystemService` (Binder).
    -   Data path: `ParcelFileDescriptor` (Ashmem) passed to service for high-throughput writes.

## Detailed Functionality

### Core Management
-   **`startInstallation(String dsuSlot)`**: Initializes a new installation context.
-   **`createPartition(String name, long size, boolean readOnly)`**:
    -   Creates a partition for the DSU (e.g., "system", "userdata").
    -   Returns a `Pair<Integer, Session>`.
    -   Status code corresponds to `IGsiService.INSTALL_*`.
-   **`closePartition()`**: Closes the currently active partition write stream.
-   **`finishInstallation()`**: Marks the installation sequence as complete.
-   **`abort()`**: Cancels an active installation.
-   **`remove()`**: Deletes an existing DSU installation.
-   **`setEnable(boolean enable, boolean oneShot)`**:
    -   Toggles the DSU.
    -   `oneShot=true` means it boots once then reverts (Sticky bit).

### Session Management (Inner Class)
The `Session` class encapsulates operations valid only during an active partition creation.
-   **`setAshmem(ParcelFileDescriptor ashmem, long size)`**:
    -   Sets up a shared memory region for data transfer.
    -   Crucial for performance (avoids copying large chunks via Binder transaction limits).
-   **`submitFromAshmem(int size)`**:
    -   Tells the service to read `size` bytes from the previously configured Ashmem FD and write them to the current partition.
-   **`commit()`**:
    -   Calls `mService.setEnable(true, true)`. Effectively finishes and enables one-shot boot.
-   **`getAvbPublicKey(AvbPublicKey dst)`**: Retrieves verification metadata.

### State Queries
-   **`isInUse()`**: Is the device currently booted into a Dynamic System?
-   **`isInstalled()`**: Is a DSU installed (but not necessarily running)?
-   **`isEnabled()`**: Is the DSU set to boot next time?
-   **`getInstallationProgress()`**: Returns `GsiProgress` struct.

## Data Model

### Dependencies
-   `android.gsi.GsiProgress`: Struct containing status, bytes processed, total bytes.
-   `android.gsi.AvbPublicKey`: Struct for AVB key data.
-   `android.gsi.IGsiService`: Constants used for return codes.

### Helper Structs
**Session**
-   Ephemeral object created by `createPartition`.
-   Not thread-safe; assumes sequential write operations.

## API Reference
See `IDynamicSystemService.aidl` for the definitive contract.
-   `startInstallation`
-   `createPartition` -> `Session`
-   `closePartition`
-   `finishInstallation`
-   `setEnable`
-   `remove`
-   `getInstallationProgress`

## Java-to-C++ Translation Guide

### Architecture
-   This class is a thin wrapper around `IDynamicSystemService`. The C++ implementation should likely interact directly with the Binder interface `android::os::image::IDynamicSystemService` or the lower-level `android::gsi::IGsiService`.

### Shared Memory (Ashmem)
-   **Java**: `ParcelFileDescriptor` wrapping an Ashmem region.
-   **C++**:
    -   Use `memfd_create` or `ashmem_create_region`.
    -   Pass the File Descriptor (int) via Binder (`dup` it if necessary).
    -   Use `mmap` to write data into the region before calling `submitFromAshmem`.

### Error Handling
-   Java throws `RuntimeException` wrapping `RemoteException`.
-   C++ should check `binder::Status` returned by AIDL calls.

### Specific Translations
| Java | C++ |
| :--- | :--- |
| `DynamicSystemManager` | `sp<IDynamicSystemService>` client wrapper |
| `ParcelFileDescriptor` | `base::unique_fd` or raw `int` fd |
| `Session` | A struct or helper class holding the interface pointer + current state. |
| `submitFromAshmem` | `service->submitFromAshmem(bytes)` |

## Implementation Risks
-   **Ashmem Lifecycle**: Ensure the FD is kept open long enough for the service to map it, but closed properly to avoid leaks. In Binder, passing an FD usually duplicates it, so local closure is safe, but verify `IDynamicSystemService` semantics.
-   **Concurrency**: The `Session` writes invoke IPC. While Ashmem reduces data copy, the `submit` call is synchronous. Ensure the writer thread doesn't block the UI (not an issue for C++ background services usually).

## Questions for C++ Team
1.  Is the goal to implement a C++ client that *installs* GSIs (replacing `DynamicSystemInstallationService` logic or acting as a CLI installer)?
2.  If replacing the service: The logic heavily depends on `libgsi` / `gsid`.