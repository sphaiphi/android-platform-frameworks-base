# IWearableSensingManager - Reverse Engineering Documentation

## Executive Summary
This AIDL interface defines the communication contract between clients (via `WearableSensingManager`) and the `WearableSensingService` (system server). It manages secure connections, data streams, and hotword recognition for wearable devices.

## Architecture Overview
-   **Type**: AIDL Interface
-   **Package**: `android.app.wearable`
-   **Permissions**: All methods require `android.Manifest.permission.MANAGE_WEARABLE_SENSING_SERVICE`.
-   **Dependencies**: `IWearableSensingCallback`, `RemoteCallback`, `ParcelFileDescriptor`, `PersistableBundle`, `SharedMemory`, `ComponentName`, `PendingIntent`.

## Detailed Functionality

### Connection Management
-   **`provideConnection`**: Provides a single connection.
-   **`provideConcurrentConnection`**: Provides a connection allowing concurrency, returns a connection ID.
-   **`removeConnection`**: Removes a specific connection by ID.
-   **`removeAllConnections`**: Clears all connections.
-   **`getAvailableConnectionCount`**: Returns quota for concurrent connections.

### Data & Stream Management
-   **`provideReadOnlyParcelFileDescriptor`**: Sends a read-only PFD with metadata.
-   **`provideDataStream`**: Sends a PFD and a callback for reverse file access.
-   **`provideData`**: Sends configuration (`PersistableBundle`) and large data (`SharedMemory`).

### Observers
-   **`registerDataRequestObserver`**: Registers a `PendingIntent` to be triggered on data requests.
-   **`unregisterDataRequestObserver`**: Unregisters the observer.

### Hotword
-   **`startHotwordRecognition`**: Initiates hotword listening.
-   **`stopHotwordRecognition`**: Stops hotword listening.

## API Reference
*All methods allow `RemoteException`.*

| Method | Parameters | Return | Description |
| :--- | :--- | :--- | :--- |
| `getAvailableConnectionCount` | None | `int` | Returns remaining connection slots. |
| `provideConnection` | `pfd`, `callback`, `statusCallback` | `void` | Legacy/Single connection provision. |
| `provideConcurrentConnection` | `pfd`, `metadata`, `callback`, `statusCallback` | `int` | Concurrent connection provision. Returns ID. |
| `removeConnection` | `connectionId` | `boolean` | Removes connection by ID. |
| `removeAllConnections` | None | `void` | Removes all connections. |
| `provideReadOnlyParcelFileDescriptor` | `pfd`, `metadata`, `statusCallback` | `void` | Provides read-only file descriptor. |
| `provideDataStream` | `pfd`, `callback`, `statusCallback` | `void` | Provides data stream with callback. |
| `provideData` | `data`, `sharedMemory`, `callback` | `void` | Provides bundle and shared memory. |
| `registerDataRequestObserver` | `dataType`, `intent`, `statusCallback` | `void` | Registers data observer. |
| `unregisterDataRequestObserver` | `dataType`, `intent`, `statusCallback` | `void` | Unregisters data observer. |
| `startHotwordRecognition` | `componentName`, `statusCallback` | `void` | Starts hotword recognition. |
| `stopHotwordRecognition` | `statusCallback` | `void` | Stops hotword recognition. |

## Java-to-C++ Translation Guide
-   **`PersistableBundle`**: Map to `android::os::PersistableBundle` (C++).
-   **`ParcelFileDescriptor`**: Map to `android::os::ParcelFileDescriptor` or raw generic file descriptor handling.
-   **`SharedMemory`**: Map to `AMemory` or `android::os::SharedMemory`.
-   **`RemoteCallback`**: Requires a Binder callback implementation.
-   **`PendingIntent`**: passed as opaque `Parcelable` object usually.

## Implementation Risks
-   **Permission Checks**: C++ implementation of the service must enforce `MANAGE_WEARABLE_SENSING_SERVICE`.
-   **Concurrency**: Handling multiple concurrent connections requires thread-safe state management in the service.
