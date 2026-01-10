# LoaderManager - Reverse Engineering Documentation

## Executive Summary
`LoaderManager` is an abstract class associated with an `Activity` or `Fragment` for managing one or more `Loader` instances. It facilitates long-running operations (like database queries via `CursorLoader`) by tying their lifecycle to the UI component's lifecycle, ensuring that data is retained across configuration changes and that resources are cleaned up when the UI is destroyed. It is now deprecated in favor of `ViewModel` and `LiveData`.

## Architecture Overview
- **Implementation**: The primary implementation is `LoaderManagerImpl`.
- **Inner Classes**:
    - `LoaderCallbacks<D>`: Interface for client code to receive data and lifecycle events from loaders.
    - `LoaderInfo`: An internal container that wraps a `Loader` and its state (data, listeners, started/stopped status).
- **Management**: Uses `SparseArray` to track active and inactive loaders by their IDs.

## Detailed Functionality

### initLoader(int id, Bundle args, LoaderCallbacks<D> callback)
**Purpose**: Initializes or reuses a loader with a specific ID.
**Algorithm**:
1. Checks if a loader with the given ID already exists.
2. If it doesn't exist, it creates a new one via `callback.onCreateLoader`.
3. If it exists, it updates the callback and, if data is already available, immediately calls `onLoadFinished`.

### restartLoader(int id, Bundle args, LoaderCallbacks<D> callback)
**Purpose**: Forces the creation of a new loader, potentially replacing an existing one.
**Algorithm**:
1. If an existing loader is active, it is marked as "inactive" and scheduled for destruction once the new loader has data.
2. If an inactive loader already exists for that ID, it is destroyed.
3. A new loader is created and started.

### Lifecycle Integration (`doStart`, `doStop`, `doDestroy`)
**Purpose**: Synchronizes loader states with the host Activity/Fragment.
**Logic**:
- `doStart()`: Iterates through all loaders and calls `start()`.
- `doStop()`: Iterates through all loaders and calls `stop()`.
- `doDestroy()`: Cleans up and resets all loaders, releasing their data and unregistering listeners.

### Data Delivery (`onLoadComplete`)
**Purpose**: Receives data from the `Loader` and delivers it to the client.
**Algorithm**:
1. Checks if the loader is still active and hasn't been destroyed.
2. Updates internal data cache.
3. Invokes `callback.onLoadFinished` on the main thread.
4. If there were inactive loaders waiting for this new data to be ready, they are now destroyed.

## API Reference
- `initLoader(...)`: Ensures a loader is initialized.
- `restartLoader(...)`: Re-creates a loader.
- `destroyLoader(int id)`: Removes and cleans up a specific loader.
- `getLoader(int id)`: Retrieves a loader by its ID.

## Java-to-C++ Translation Guide
- **Async Operations**: Use `std::future`, `std::promise`, or a task-based system like `android::WorkerThread` to implement the loading logic.
- **Lifecycle Mapping**: Bind the C++ `LoaderManager` equivalent to the lifecycle of the C++ Activity/View component. Use RAII to ensure destruction calls `doDestroy`.
- **Data Callbacks**: Use function pointers, `std::function`, or an observer pattern to deliver results back to the UI.
- **Thread Safety**: Ensure all interactions with `LoaderCallbacks` occur on the UI thread, while the loading happens on a background thread.

## Implementation Risks
- **Memory Management**: Loaders often hold onto heavy objects (like database cursors). The C++ implementation must ensure these are closed and released promptly to avoid file descriptor leaks or memory bloat.
- **Configuration Changes**: The ability to "retain" a loader across host instances is complex in C++. It typically involves moving the `LoaderManager` to a persistent scope (like a singleton or a process-wide registry) and re-attaching it to the new UI instance.
