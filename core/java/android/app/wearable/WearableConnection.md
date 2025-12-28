# WearableConnection - Reverse Engineering Documentation

## Executive Summary
`WearableConnection` is an interface representing a connection to a remote wearable device. It abstracts the underlying transport (`ParcelFileDescriptor`) and associated metadata, along with lifecycle callbacks for connection acceptance and errors.

## Architecture Overview
-   **Type**: Interface
-   **Package**: `android.app.wearable`
-   **Usage**: Implemented by clients to wrap their wearable connection before passing it to `WearableSensingManager`.

## Detailed Functionality

### Core Components
1.  **Connection Handle**: A `ParcelFileDescriptor` representing the raw connection (e.g., Bluetooth socket).
2.  **Metadata**: A `PersistableBundle` containing identification or configuration for the connection.
3.  **Lifecycle Callbacks**:
    -   `onConnectionAccepted()`: Notifies when the service has accepted the connection.
    -   `onError(int errorCode)`: Notifies of errors during setup.

## Data Model
-   **`getConnection()`**: Returns `ParcelFileDescriptor`.
-   **`getMetadata()`**: Returns `PersistableBundle`.

## API Reference
-   `ParcelFileDescriptor getConnection()`: Get the file descriptor.
-   `PersistableBundle getMetadata()`: Get metadata.
-   `void onConnectionAccepted()`: Callback for success.
-   `void onError(@WearableSensingManager.StatusCode int errorCode)`: Callback for failure.

## Java-to-C++ Translation Guide
-   This is a client-side interface. In C++, this would likely be a struct or abstract base class holding the FD and metadata, with function pointers or virtual methods for callbacks.
-   **Callbacks**: In C++, these might be implemented via `std::function` or listener interfaces.

## Special Attention Areas
-   **Ownership**: The `ParcelFileDescriptor` returned by `getConnection` is likely owned by the caller but shared with the system. Ensure proper `dup()` or ref-counting if needed in C++.
