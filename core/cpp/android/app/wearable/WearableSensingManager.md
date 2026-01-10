# WearableSensingManager - Reverse Engineering Documentation

## Executive Summary
`WearableSensingManager` is the system service manager class that provides the API for apps to interact with the `WearableSensingService`. It handles connection lifecycle, data transmission, and hotword detection requests, acting as a wrapper around `IWearableSensingManager`.

## Architecture Overview
-   **Type**: System Service Manager (`getSystemService(Context.WEARABLE_SENSING_SERVICE)`)
-   **Package**: `android.app.wearable`
-   **Underlying Service**: `IWearableSensingManager` (Binder proxy).
-   **State**: Maintains a map of `WearableConnection` to `connectionId`.

## Detailed Functionality

### Connection Management
-   **`provideConnection(WearableConnection, Executor)`**:
    -   Registers a callback wrapper that handles status updates.
    -   Maps the `WearableConnection` object to a placeholder ID initially.
    -   Calls service `provideConcurrentConnection`.
    -   Updates map with real ID on return.
    -   Triggers `onConnectionAccepted` or `onError` on the `WearableConnection` via the callback.
-   **`removeConnection`**:
    -   Retrieves ID from map.
    -   Calls service `removeConnection`.
    -   Removes map entry.
-   **Legacy**: `provideConnection(ParcelFileDescriptor, ...)` for single connection mode.

### Data Handling
-   **`provideData`**: Proxies to service. Wraps status consumer in `RemoteCallback`.
-   **`provideDataStream`**:
    -   Checks `ALLOW_WEARABLE_SENSING_SERVICE_FILE_READ` change ID.
    -   If enabled, creates `IWearableSensingCallback` to allow service to open files from app context.
    -   Proxies to service.

### Observers & Hotword
-   Wrappers around `registerDataRequestObserver`, `startHotwordRecognition`, etc., converting `Executor` + `Consumer` into `RemoteCallback`.

### File Access Callback (`createWearableSensingCallback`)
-   Creates a Stub of `IWearableSensingCallback`.
-   On `openFile(filename, future)`:
    -   Opens file in `mContext.getFilesDir()`.
    -   Returns `ParcelFileDescriptor` (read-only) via future.
    -   Handles errors (FileNotFound).
    -   Closes PFD after future completion (transfer ownership?). *Note: Logic seems to close it locally, ensure future keeps it alive or dup is passed.*

## Data Model
-   `mWearableConnectionIdMap`: `ConcurrentHashMap<WearableConnection, Integer>` mapping objects to integer IDs.

## API Reference
(See Java file for full signature list. Key methods listed in functionality.)
-   **Status Codes**: `STATUS_SUCCESS`, `STATUS_ACCESS_DENIED`, `STATUS_CHANNEL_ERROR`, etc.

## Java-to-C++ Translation Guide
-   **Service Proxy**: This class is a client-side wrapper. In C++, this would be a client library wrapping the Binder interface.
-   **Callbacks**: Heavily relies on `RemoteCallback` (one-shot binder callback).
-   **Map**: Use `std::map` or `std::unordered_map` with mutexes for `mWearableConnectionIdMap`.
-   **File I/O**: `openFile` logic needs equivalent POSIX `open()` relative to app data dir if implementing client logic.

## Implementation Risks
-   **Map Synchronization**: `mWearableConnectionIdMap` access must be thread-safe (Java uses ConcurrentHashMap).
-   **Callback Lifetimes**: Ensure callbacks don't fire for removed connections (logic exists in `provideConnection` status callback).
-   **File Descriptor Leaks**: `openFile` callback logic in Java closes the PFD after completing the future. Ensure C++ `Future` implementation duplicates the FD or takes ownership correctly.
