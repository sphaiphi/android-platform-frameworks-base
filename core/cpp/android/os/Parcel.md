# Parcel - Reverse Engineering Documentation

## Executive Summary
`Parcel` is a highly optimized container for IPC (Inter-Process Communication) messages. It reads and writes data to a shared memory buffer that is passed to the kernel Binder driver. It supports primitives, arrays, Parcelables, Bundles, and active objects like Binders and FileDescriptors.

## Architecture Overview
-   **Role**: IPC Serialization Buffer.
-   **Native Peer**: `android::Parcel` (C++). `mNativePtr` points to the native instance.
-   **Access**: Methods often map 1:1 to JNI calls (`nativeWriteInt`, `nativeReadString`, etc.).

## Detailed Functionality

### Primitives
-   Reads/Writes byte, int, long, float, double, string.
-   **Endianness**: Host order (Binder is local-only or strictly controlled).

### Active Objects
-   **Binders**: Written as a flat binder object struct (handle/cookie).
-   **File Descriptors**: Written using `FLAT_BINDER_FLAG_ACCEPTS_FDS` logic in kernel. `ParcelFileDescriptor` wraps the Java side.

### Containers
-   **Typed**: `writeTypedList`, `createTypedArrayList` (for Parcelables).
-   **Untyped**: `readValue`/`writeValue` handles polymorphic types (Integer, String, Map, etc.) by writing a type tag integer first.

### Pooling
-   Maintains a static pool (`sOwnedPool`, `sHolderPool`) to reduce allocation overhead of the `Parcel` Java wrapper objects.

## Java-to-C++ Translation Guide
-   **Direct Mapping**: The C++ `android::Parcel` class is the exact equivalent.
-   **API**:
    -   `writeInt` -> `writeInt32`
    -   `writeStrongBinder` -> `writeStrongBinder`
    -   `readFileDescriptor` -> `readFileDescriptor`
-   **Safety**: `Parcel` is not thread-safe.
-   **Persistence**: NOT for persistent storage. Internal format changes between Android versions.

## Implementation Risks
-   **Buffer Size**: IPC buffer is limited (1MB shared for process). Sending large data throws `TransactionTooLargeException`.
-   **Object Lifecycle**: Writing a Binder keeps the process alive. Writing a File Descriptor dups it.
