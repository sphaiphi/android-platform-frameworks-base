# ParcelFileDescriptor - Reverse Engineering Documentation

## Executive Summary
`ParcelFileDescriptor` (PFD) is a `Parcelable` wrapper around a native `FileDescriptor`. It is the standard mechanism for transferring open files, sockets, and pipes between processes.

## Architecture Overview
-   **Role**: FD Container / Ownership Manager.
-   **Ownership**:
    -   Can "own" the FD (closes it on `close()`).
    -   Can be a "dup" (independent close).
-   **Communication**: Supports an optional "Comm Socket" (`mCommFd`) paired with the main FD. This allows sending status/errors (like "Remote side crashed") back to the sender even for simple file streams.

## Detailed Functionality

### Creation
-   **`open(File, mode)`**: Opens a file.
-   **`createPipe()`, `createSocketPair()`**: Creates pairs of PFDs for IPC.
-   **`fromFd(fd)`**: Dups or adopts an existing FD.

### Reliability (`mCommFd`)
-   When creating a pipe/socket pair (`createReliablePipe`), a second socket pair is created.
-   **`checkError()`**: Reads from `mCommFd`. If the other side closed with an error or died, this read returns the status.
-   **`closeWithError(msg)`**: Writes an error status to `mCommFd` before closing.

### Auto-Close Streams
-   `AutoCloseInputStream` / `AutoCloseOutputStream`: Helper streams that close the PFD when they are closed.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::base::unique_fd` (for ownership) or `int` (raw).
-   **Binder**: `Parcel::writeFileDescriptor`.
-   **Reliability**: The `mCommFd` pattern is a Java-framework convention. Pure C++ binders usually handle death notifications via `linkToDeath` rather than a side-channel socket, but if interacting with Java PFDs, C++ code must respect this if it wants to participate in the error reporting protocol (uncommon for native services).

## Implementation Risks
-   **Leaks**: Failing to close a PFD leaks the kernel FD.
-   **Detaching**: `detachFd()` releases ownership, leaving the user responsible for closing the native int.
