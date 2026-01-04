# DdmHandleHello - Reverse Engineering Documentation

## Executive Summary
`DdmHandleHello` manages the initial handshake between the application and the DDM server (DDMS/Android Studio). It handles "HELO" (Hello) and "FEAT" (Features) chunks and can send "WAIT" chunks when waiting for a debugger.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Registration**: Registers for:
    - `CHUNK_HELO` (`0x48454C4F`)
    - `CHUNK_FEAT` (`0x46454154`)
    - `CHUNK_WAIT` (`0x57414954`) (Sender only)

## Detailed Functionality

### `handleHELO`
**Purpose**: Responds to the initial handshake.
**Algorithm**:
1.  Reads `serverProtoVers` (int) from request (mostly ignored).
2.  Gathers system info:
    - VM Name/Version
    - App/Package Name (via `DdmHandleAppName`)
    - Instruction Set (32/64 bit, specific arch)
    - VM Flags ("CheckJNI")
    - Native Debuggable state
    - Boot Stage (added in API 34)
3.  Constructs response `ByteBuffer`.
4.  Checks `Debug.waitingForDebugger()`. If true, sends a "WAIT" chunk separately.
5.  Returns the "HELO" response chunk.

### `handleFEAT`
**Purpose**: Reports supported features to the debugger.
**Algorithm**:
1.  Retrieves VM features (`Debug.getVmFeatureList()`).
2.  Retrieves Framework features (`Debug.getFeatureList()`).
3.  Constructs response buffer containing the count and length-prefixed strings for all features.

### `sendWAIT`
**Purpose**: Notifies the debugger that the app is waiting for it to attach.
**Payload**: A single byte indicating reason (0 = waiting for debugger).

## Data Model

### HELO Response Format
**Type**: `0x48454C4F`
**Payload**:
```
[4 bytes] Client Protocol Version (1)
[4 bytes] Process ID
[4 bytes] VM Ident Length (L1)
[4 bytes] App Name Length (L2)
[L1 * 2 bytes] VM Ident String
[L2 * 2 bytes] App Name String
[4 bytes] User ID
[4 bytes] Instruction Set Length (L3)
[L3 * 2 bytes] Instruction Set String
[4 bytes] VM Flags Length (L4)
[L4 * 2 bytes] VM Flags String
[1 byte]  Is Native Debuggable (0/1)
[4 bytes] Package Name Length (L5)
[L5 * 2 bytes] Package Name String
[4 bytes] Stage (Int, added in API 34)
```

### FEAT Response Format
**Type**: `0x46454154`
**Payload**:
```
[4 bytes] Feature Count (N)
For i = 0 to N-1:
    [4 bytes] Feature String Length (L)
    [L * 2 bytes] Feature String
```

## Java-to-C++ Translation Guide
- **System Properties**: Accessing `java.vm.name` etc. requires equivalent NDK/System property calls in C++.
- **Feature Lists**: The C++ implementation needs to define what features the native layer supports (e.g., "opengl-tracing", "view-hierarchy").
- **DdmSyncState**: The "Stage" integer is specific to Android's boot process.

## Implementation Risks
- **Protocol Versioning**: The structure of the HELO packet implies versions. The C++ implementation must match the expected fields of the connected DDMS client.
