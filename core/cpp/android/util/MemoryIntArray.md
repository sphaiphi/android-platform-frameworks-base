# MemoryIntArray - Reverse Engineering Documentation

## Executive Summary
A shareable array of integers backed by shared memory (ashmem/memfd). Designed for efficient inter-process communication (IPC) where one process owns/writes and others read.

## Architecture Overview
*   **Backing**: Native file descriptor (`mFd`) mapping a shared memory region.
*   **Ownership**: `mIsOwner` flag. Only owner can write.
*   **Parcelable**: Can be sent via Binder. The FD is transferred.

## Key Algorithms
*   **Native Methods**: `nativeCreate`, `nativeOpen`, `nativeGet`, `nativeSet`.
*   **Locking**: Relies on atomic memory operations at the CPU level for individual reads/writes, but no high-level synchronization.

## Java-to-C++ Translation Guide
*   **Shared Memory**: Use `memfd_create` or `ashmem_create_region`.
*   **Mapping**: `mmap`.
*   **Access**: Direct pointer access (`int*`). `std::atomic<int>` might be appropriate if concurrent access is expected.

## Implementation Risks
*   **Lifetime**: The memory must remain valid as long as any process has it mapped.
*   **Security**: Writable mappings should only be held by the owner.
