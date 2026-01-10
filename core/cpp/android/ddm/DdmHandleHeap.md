# DdmHandleHeap - Reverse Engineering Documentation

## Executive Summary
`DdmHandleHeap` handles the "HPGC" (Heap Garbage Collection) chunk, allowing the debugger to force a garbage collection event in the VM.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Registration**: Registers for `CHUNK_HPGC` (`0x48504743`).

## Detailed Functionality

### `handleChunk`
**Purpose**: Dispatches based on chunk type.
**Logic**: Only handles `HPGC`. Throws exception for others.

### `handleHPGC`
**Purpose**: Performs garbage collection.
**Algorithm**:
1.  Calls `Runtime.getRuntime().gc()`.
2.  Returns `null` (no response packet needed).

## Java-to-C++ Translation Guide

### Garbage Collection
- **Java**: `Runtime.getRuntime().gc()` triggers the JVM GC.
- **C++**: This is specific to the managed runtime (ART). In a pure C++ context, this might map to nothing or a specific memory allocator trim operation (e.g., `malloc_trim`). If this C++ code is part of the ART runtime itself, it should invoke the internal GC mechanism.

### Chunk Format (HPGC)
**Type**: `0x48504743` ("HPGC")
**Payload**: Empty or ignored.
