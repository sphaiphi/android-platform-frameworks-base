# MemoryFile - Reverse Engineering Documentation

## Executive Summary
`MemoryFile` is a wrapper around `SharedMemory` (Ashmem) that exposes it as a standard Java `InputStream` / `OutputStream`. It was the legacy way to use shared memory before `SharedMemory` class was introduced.

## Architecture Overview
-   **Backing**: `SharedMemory` object.
-   **Access**: Maps the shared memory via `mSharedMemory.mapReadWrite()`.
-   **Streams**: Inner classes `MemoryInputStream` and `MemoryOutputStream` read/write directly to the `ByteBuffer` mapping.

## Detailed Functionality
-   **`readBytes` / `writeBytes`**: Copies data between the mapped buffer and user arrays.
-   **Purging**: Supports `allowPurging(boolean)` (pinning/unpinning ashmem). This interacts with the kernel's ashmem driver to allow the OS to reclaim the memory if under pressure.

## Java-to-C++ Translation Guide
-   **Equivalent**: `IMemory` (Binder), `Ashmem`.
-   **Modern Usage**: Use `memfd_create` (if available) or `ashmem_create_region`.
-   **Mapping**: `mmap`.
-   **Streams**: Use standard C++ `memcpy` or custom stream buffers over the raw pointer.

## Implementation Risks
-   **Pinning**: The pinning logic (`native_pin`) is specific to Ashmem. Standard `memfd` does not support this exact semantics (it supports sealing, but not "discard on pressure and notify").
