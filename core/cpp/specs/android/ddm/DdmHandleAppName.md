# DdmHandleAppName - Reverse Engineering Documentation

## Executive Summary
`DdmHandleAppName` manages the "APNM" (Application Name) DDM chunk. It tracks the application's name and package name and sends this information to the DDM server (DDMS/Android Studio) upon connection or when the app name is set.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Singleton**: Uses a singleton pattern (`mInstance`), though methods are largely static or triggered via DDM registration.
- **State**: Maintains global static state for the current app name and package name.

## Detailed Functionality

### `setAppName`
**Purpose**: Sets the application and package names and triggers an update to the DDM server.
**Algorithm**:
1.  Validates inputs (non-null, non-empty).
2.  Updates the static `sNames` instance.
3.  Calls `sendAPNM` to transmit the new names.

### `sendAPNM`
**Purpose**: Constructs and sends the "APNM" chunk.
**Algorithm**:
1.  Allocates a `ByteBuffer`.
    - Size: 4 (appLen) + appLen*2 + 4 (userId) + 4 (pkgLen) + pkgLen*2.
2.  Writes:
    - App Name Length (int)
    - App Name (String, 16-bit chars)
    - User ID (int)
    - Package Name Length (int)
    - Package Name (String, 16-bit chars)
3.  Wraps buffer in a `Chunk` (type "APNM").
4.  Sends via `DdmServer.sendChunk`.

### `handleChunk`
**Purpose**: Handles incoming chunks.
**Behavior**: Returns `null`. This handler does not process inbound "APNM" packets; it only sends them.

## Data Model

### `Names` (Inner Class)
- **Fields**:
    - `mAppName` (String)
    - `mPkgName` (String)
- **Immutability**: Immutable data holder.

## API Reference

| Method | Parameters | Returns | Description |
|--------|------------|---------|-------------|
| `setAppName` | `String appName`, `String pkgName`, `int userId` | `void` | Updates names and notifies DDM server. |
| `getNames` | None | `Names` | Returns the current names. |

## Java-to-C++ Translation Guide

### Singleton/Static State
- **Java**: Uses `static volatile Names sNames`.
- **C++**: Use a thread-safe singleton or static atomic pointer to hold the names configuration.

### Chunk Format (APNM)
**Type**: `0x41504E4D` ("APNM")
**Payload**:
```
[4 bytes] App Name Length (N)
[N * 2 bytes] App Name (UTF-16BE)
[4 bytes] User ID
[4 bytes] Package Name Length (M)
[M * 2 bytes] Package Name (UTF-16BE)
```

## Implementation Risks
- **Concurrency**: `setAppName` might be called from multiple threads. In Java, `sNames` is volatile, but `sendAPNM` is stateless regarding the static variable (it takes args). Ensure C++ implementation handles concurrent setting correctly if applicable.
