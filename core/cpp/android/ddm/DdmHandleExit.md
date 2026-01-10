# DdmHandleExit - Reverse Engineering Documentation

## Executive Summary
`DdmHandleExit` handles the "EXIT" DDM chunk, allowing a connected debugger/DDMS to terminate the application process with a specific exit code.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Registration**: Registers for `CHUNK_EXIT` (`0x45584954`).

## Detailed Functionality

### `handleChunk`
**Purpose**: Processes the "EXIT" chunk.
**Algorithm**:
1.  Wraps the chunk data in a `ByteBuffer`.
2.  Reads one integer: `statusCode`.
3.  Calls `Runtime.getRuntime().halt(statusCode)`.
**Side Effects**: Terminates the process immediately. `Runtime.halt` forces termination without running shutdown hooks or finalizers.

## Data Model
Stateless.

## API Reference
Standard `ChunkHandler` interface.

## Java-to-C++ Translation Guide

### Process Termination
- **Java**: `Runtime.getRuntime().halt(status)`
- **C++**: `_exit(status)` or `quick_exit(status)`. Do not use `exit()` if the intention is to mimic `halt` (which avoids cleanup).

### Chunk Format (EXIT)
**Type**: `0x45584954` ("EXIT")
**Payload**:
```
[4 bytes] Status Code (int)
```
