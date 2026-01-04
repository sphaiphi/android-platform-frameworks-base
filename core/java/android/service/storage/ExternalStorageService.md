# ExternalStorageService - Reverse Engineering Documentation

## Executive Summary
`ExternalStorageService` is a system service base class used to handle file system I/O for other applications. It is the core of Android's storage virtualization layer (Scaped Storage), typically implemented via a FUSE (Filesystem in Userspace) daemon. It allows the system to intercept, filter, and manage access to external storage volumes.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IExternalStorageService.Stub`.
*   **Threading**: Dispatches all operations to a background thread (`BackgroundThread`) to avoid blocking binder threads during heavy I/O operations.
*   **FUSE Integration**: The service receives a `deviceFd` which it uses to read FUSE requests from the kernel and write responses back.
*   **Permission**: Requires `android.permission.BIND_EXTERNAL_STORAGE_SERVICE`.

## Detailed Functionality

### Session Management
*   **`onStartSession(String sessionId, int flags, ParcelFileDescriptor deviceFd, File upperPath, File lowerPath)`**:
    *   **Goal**: Start a new storage virtualization session.
    *   **upperPath**: The path visible to applications (virtual).
    *   **lowerPath**: The actual path where data is stored (physical).
    *   **deviceFd**: The communication channel with the kernel FUSE module.
*   **`onEndSession(String sessionId)`**: Terminates the virtual storage session and cleans up resources.

### Volume & Cache Management
*   **`onVolumeStateChanged(StorageVolume vol)`**: Called when a volume's state changes (e.g., MOUNTED, UNMOUNTED). The service must process this before the state change is broadcast to the rest of the system.
*   **`onFreeCache(UUID volumeUuid, long bytes)`**: Requests the service to delete cached files to free up disk space.

### Diagnostics
*   **`onAnrDelayStarted(String packageName, int uid, int tid, int reason)`**: Called if an application is about to trigger an ANR because it is blocked on I/O handled by this service. This allows the service to show a "Loading..." UI.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.storage.ExternalStorageService"`
*   `FLAG_SESSION_TYPE_FUSE`: Indicates the session uses the FUSE kernel module.

## Java-to-C++ Translation Guide

### FUSE Implementation
*   **Java**: The service receives the `deviceFd`.
*   **C++**: The actual FUSE request loop is almost always implemented in C++ for performance. The `ExternalStorageService` in Java typically acts as a management bridge, while a native daemon (like `MediaProvider`'s FUSE loop) handles the raw `read`/`write` calls on the `deviceFd`.

### Data Structures
*   `StorageVolume`, `ParcelFileDescriptor`, `RemoteCallback`.
*   Error handling uses `ParcelableException` to pass native errors back to Java.

## Implementation Risks
*   **Performance**: Since every file operation in the virtualized storage passes through this service (via FUSE), any latency or bottleneck here impacts the entire system's storage performance.
*   **Stability**: If this service crashes, all apps accessing external storage will hang or receive I/O errors.
*   **Deadlocks**: Must be extremely careful not to perform I/O on the "upper" path within the service logic, as it could cause a recursive deadlock.
