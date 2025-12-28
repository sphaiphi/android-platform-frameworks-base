# IWearableSensingCallback - Reverse Engineering Documentation

## Executive Summary
This AIDL interface defines a callback mechanism for the `WearableSensingService`. It allows the service to request the opening of files from the client application, receiving the file descriptor asynchronously via an `AndroidFuture`.

## Architecture Overview
- **Type**: `oneway interface` (Asynchronous IPC)
- **Package**: `android.app.wearable`
- **Role**: Callback interface passed from the client (via `WearableSensingManager`) to the system service.

## Detailed Functionality

### `openFile`
**Purpose**: Requests the client to open a specific file and return its file descriptor.
**Algorithm**:
1.  Service calls `openFile(filename, future)`.
2.  Client receives the call.
3.  Client attempts to open the file (typically in its local storage).
4.  Client completes the `AndroidFuture` with the `ParcelFileDescriptor` or an error.

**Java-Specific Notes**:
-   Uses `com.android.internal.infra.AndroidFuture` for asynchronous result delivery.
-   `ParcelFileDescriptor` is used for passing file handles across IPC boundaries.

**C++ Implementation Guidance**:
-   Implement as an AIDL callback class.
-   `AndroidFuture` maps to a future/promise pattern in C++ (Binder callbacks).
-   Ensure file descriptor ownership is correctly transferred.

## API Reference

### `void openFile(in String filename, in AndroidFuture<ParcelFileDescriptor> future)`
-   **filename**: Name of the file to open.
-   **future**: A future to be completed with the `ParcelFileDescriptor` of the opened file.

## Java-to-C++ Translation Guide
-   `oneway`: Indicates functions should return `void` and not block the caller.
-   `AndroidFuture`: Requires a binder-compatible callback mechanism in C++.
