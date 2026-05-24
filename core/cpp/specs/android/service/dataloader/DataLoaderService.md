# DataLoaderService - Reverse Engineering Documentation

## Executive Summary
`DataLoaderService` is the base class for implementing a data loader used in the Android Incremental File System (Incremental Install). It provides the actual data bytes for a streaming installation session, allowing apps to be launched before they are fully downloaded.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **JNI Centric**: Most operations are delegated to native methods that interface with the Incremental Service and the `incfs` kernel module.
*   **IPC**: Implements `IDataLoader.Stub`.
*   **Session Lifecycle**: Bound by the system during an installation session. It is automatically rebound if it crashes or is killed until the session has enough data.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IDataLoader` binder interface.

### `IDataLoader.Stub` Implementation (Internal)
*   **`create`**: Calls `nativeCreateDataLoader`. Initializes the data loader with params and file system control handles (command, pending reads, log, blocks written FDs).
*   **`start`/`stop`/`destroy`**: Lifecycle management delegated to native code.
*   **`prepareImage`**: Calls `nativePrepareImage`.

### `DataLoader` Interface (Inner)
Applications must implement this to handle specific installation sessions.
*   **`onCreate`**: Initialization. Receives `DataLoaderParams` and a `FileSystemConnector`.
*   **`onPrepareImage`**: The main worker method. It should block until the required files are ready. It uses `FileSystemConnector.writeData` to stream data.

### `FileSystemConnector` (Inner)
A wrapper provided to the `DataLoader` to write data into the system's installation image.
*   **`writeData(name, offset, length, incomingFd)`**: Streams bytes from an arbitrary file descriptor into a named file in the installation session.

## Java-to-C++ Translation Guide

### JNI Bridge
The class is a thin Java wrapper around a C++ implementation. The core logic resides in native methods:
*   `nativeCreateDataLoader`
*   `nativeStartDataLoader`
*   `nativeStopDataLoader`
*   `nativeDestroyDataLoader`
*   `nativePrepareImage`
*   `nativeWriteData`

### File System Handles
*   The `FileSystemControlParcel` contains multiple `ParcelFileDescriptor` objects. In C++, these are raw file descriptors used to communicate with the `incfs` kernel module.

### Performance
*   Data loaders often perform network I/O (streaming from a cloud provider). The `FileSystemConnector.writeData` method is the critical path for performance.

## Implementation Risks
*   **Native Stability**: Crashes in the native data loader implementation can interrupt installation.
*   **Resource Management**: Must carefully close the file descriptors passed in `FileSystemControlParcel`.
*   **Permissions**: Writing data requires `INSTALL_PACKAGES` permission.
