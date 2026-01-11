# DdmHandleNativeHeap - Reverse Engineering Documentation

## Executive Summary
`DdmHandleNativeHeap` handles the "NHGT" (Native Heap GeT) chunk. It retrieves native heap leak information and sends it back to the debugger.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Registration**: Registers for `CHUNK_NHGT` (`0x4E484754`).

## Detailed Functionality

### `handleChunk`
**Purpose**: Processes native heap requests.
**Algorithm**:
1.  Checks type is `NHGT`.
2.  Calls `getLeakInfo()` (native method).
3.  If data exists, wraps it in a response chunk.
4.  If fail, returns a "Fail" chunk.

### `getLeakInfo`
**Type**: `native byte[]`.
**Description**: Fetches the raw leak data from the native memory allocator/profiler.

## Java-to-C++ Translation Guide
This class is essentially a JNI wrapper around a C++ implementation.
- **C++ Side**: The logic inside `getLeakInfo` is what needs to be preserved or exposed. It likely interacts with `malloc_debug` or similar Android internal memory tools.
- **Chunk Handling**: The C++ replacement would handle the `NHGT` chunk directly and output the binary blob.

### Chunk Format (NHGT)
**Type**: `0x4E484754`
**Payload**:
- **Response**: Arbitrary binary data (opaque to the Java layer, defined by the native heap profiler format).
