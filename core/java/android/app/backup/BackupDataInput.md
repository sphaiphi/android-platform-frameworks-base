# BackupDataInput - Reverse Engineering Documentation

## Executive Summary
`BackupDataInput` provides a structured interface for reading data entities from a backup restore stream. It acts as a wrapper around a file descriptor (usually a pipe from the transport) and parses the entity headers and data.

## Architecture Overview
-   **Role**: Data Reader.
-   **Dependencies**: Native methods (`readNextHeader_native`, `readEntityData_native`, etc.).
-   **Usage**: Used within `BackupAgent.onRestore` to iterate over entities.

## Detailed Functionality

### Initialization
-   **Constructor**: Takes a `FileDescriptor`. Calls native `ctor`.
-   **Native State**: Holds a pointer `mBackupReader` to the native reader state.

### Reading Entities
-   **`readNextHeader()`**: Advances to the next entity. Parses the key and data size. Returns `true` if an entity exists, `false` at EOF.
-   **`getKey()`**: Returns the key of the current entity.
-   **`getDataSize()`**: Returns the payload size of the current entity.
-   **`readEntityData(byte[], int, int)`**: Reads raw bytes for the current entity. Can be called multiple times until `dataSize` is consumed.
-   **`skipEntityData()`**: Efficiently skips the current entity payload.

## Data Model
-   `mBackupReader`: `long` (native pointer).
-   `mHeader`: `EntityHeader` (caches key/size).

## API Reference
-   `readNextHeader()`
-   `readEntityData(...)`
-   `skipEntityData()`
-   `getKey()`, `getDataSize()`

## Java-to-C++ Translation Guide
-   **Native Implementation**: This class is a thin JNI wrapper around an existing C++ implementation in the Android framework (likely `frameworks/base/libs/androidfw/BackupDataInput.cpp`).
-   **Direct Use**: The C++ team should use the underlying C++ classes (`android::BackupDataInput`) directly rather than re-implementing this wrapper.

## Implementation Risks
-   **Native Pointer Management**: `finalize()` calls `dtor()`. Ensure resource cleanup in C++ (RAII) to avoid leaks.
