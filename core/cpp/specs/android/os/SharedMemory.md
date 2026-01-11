# SharedMemory - Reverse Engineering Documentation

## Executive Summary
`SharedMemory` provides a Java API for creating and mapping anonymous shared memory regions. It abstracts over `ashmem` (Android Shared Memory) or `memfd` (Linux). It is `Parcelable` and `Closeable`.

## Architecture Overview
-   **Core**: Wraps a `FileDescriptor` pointing to the shared memory region.
-   **Lifecycle**: `Cleaner` closes the FD when the object is GC'd.
-   **Mapping**: `mapReadWrite()` / `mapReadOnly()` call `Os.mmap` to create `DirectByteBuffer`s.

## Detailed Functionality
-   **Creation**: `create(name, size)`. Calls native `nCreate`.
-   **Protection**: `setProtect(prot)`. Sets read/write/exec permissions on the region. Note: Permissions can only be removed (made stricter), not added.
-   **Parceling**: Transmits the File Descriptor. The receiving side gets a mapped FD pointing to the same physical memory.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::SharedMemory` (not standard in NDK, but exists in framework native). Or simply passing file descriptors.
-   **NDK**: `ASharedMemory_create`, `ASharedMemory_getSize`, `ASharedMemory_setProt`.
-   **Serialization**: Write the FD to the Binder parcel.

## Implementation Risks
-   **Mapping Leaks**: Users must call `SharedMemory.unmap(ByteBuffer)` to release the virtual address space.
-   **Security**: Ensure `setProtect` is used to make memory read-only before passing to untrusted clients.
