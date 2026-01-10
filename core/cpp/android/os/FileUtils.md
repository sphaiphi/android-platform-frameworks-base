# FileUtils - Reverse Engineering Documentation

## Executive Summary
`FileUtils` provides static utility methods for file manipulation, including copying data between streams/FDs with kernel optimizations (sendfile, splice), managing permissions, and handling filename validation.

## Architecture Overview
-   **Role**: Static Utility Class.
-   **Optimization**: Selects the best copy mechanism based on the source/sink types (`sendfile` for disk-to-network, `splice` for pipes, userspace buffer for streams).

## Detailed Functionality

### Copy Operations
-   **`copy(File, File)`**: Stream-based copy.
-   **`copy(InputStream, OutputStream)`**:
    -   Checks if streams wrap FileDescriptors.
    -   If so, delegates to FD-based copy.
    -   Otherwise, uses 8KB userspace buffer loop.
-   **`copy(FileDescriptor, FileDescriptor)`**:
    -   Tries `Os.sendfile` (if source is file, dest is socket/file).
    -   Tries `Os.splice` (if one end is a pipe).
    -   Fallbacks to userspace read/write.

### Permissions
-   **`setPermissions`**: Wraps `Os.chmod` and `Os.chown`.
-   **`getUid`**: Wraps `Os.stat`.

### Text I/O
-   **`readTextFile`**: Reads a file into a String, supporting "head", "tail", or "cat" modes (based on max length param).
-   **`stringToFile`**: writes String to file.

## Java-to-C++ Translation Guide
-   **Equivalents**:
    -   `android-base/file.h` (ReadFdToString, WriteStringToFd).
    -   `std::filesystem::copy`.
    -   `sendfile`, `splice` system calls directly.
-   **Logic**: The adaptive copy logic (try sendfile -> try splice -> fallback) is valuable to replicate for performance in C++ system services moving large data.

## Implementation Risks
-   **Splice Loops**: Implementing `splice` loops correctly in C++ handles `EAGAIN` and partial writes similarly to the Java implementation.
