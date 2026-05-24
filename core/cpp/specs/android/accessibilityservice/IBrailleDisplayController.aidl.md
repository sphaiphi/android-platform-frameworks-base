
# IBrailleDisplayController.aidl - Reverse Engineering Documentation

## Executive Summary
`IBrailleDisplayController` is a one-way AIDL interface that defines the contract for the system server to call back into an accessibility service's `BrailleDisplayController`. When a service initiates a connection to a Braille display, it passes a Binder object implementing this interface to the system. The system then uses this object to deliver connection status updates and input data from the device.

## Architecture Overview
*   **System-to-Service Communication**: This interface represents the "read" or "event" channel for a Braille display. It allows the `AccessibilityManagerService` (the server) to push events to the `BrailleDisplayControllerImpl` (the client) in the accessibility service's process.
*   **One-Way Interface**: The `oneway` keyword is applied to the entire interface. This is a critical design choice, meaning that all calls from the system to the service are non-blocking. The system fires the event and does not wait for the service to process it. This ensures that a slow service cannot block the system thread that is managing the device I/O.
*   **Paired Interface**: This interface is the counterpart to `IBrailleDisplayConnection.aidl`. `IBrailleDisplayController` is for system-to-service callbacks, while `IBrailleDisplayConnection` is for service-to-system commands.

## Detailed Functionality

### `onConnected(in IBrailleDisplayConnection connection, in byte[] hidDescriptor)`
*   **Purpose**: Called by the system when a connection to a Braille display has been successfully established.
*   **Parameters**:
    *   `connection`: An `IBrailleDisplayConnection` Binder proxy. This is the object the service will use to `write` data and `disconnect`.
    *   `hidDescriptor`: A `byte[]` containing the raw HID Report Descriptor from the device. This is essential for the service to understand how to parse input from the device and how to format output reports for it.
*   **Behavior**: The service's implementation of this method will store the `connection` object for future use and use the `hidDescriptor` to configure its data parser/formatter.

### `onConnectionFailed(int error)`
*   **Purpose**: Called by the system if the connection attempt fails.
*   **Parameters**:
    *   `error`: An integer error code providing the reason for the failure (e.g., device not found, permission error).

### `onInput(in byte[] input)`
*   **Purpose**: Called by the system whenever new data is received from the Braille display's input report.
*   **Parameters**:
    *   `input`: A `byte[]` containing the raw input report from the device. The service is responsible for parsing this according to the HID descriptor.

### `onDisconnected()`
*   **Purpose**: Called by the system when the connection is terminated, either because the service requested it, the device was physically unplugged, or an I/O error occurred.
*   **Behavior**: The service's implementation should clean up all state associated with the connection.

## Java-to-C++ Translation Guide
*   **Binder Interface Generation**: The AIDL compiler will generate the corresponding C++ files:
    *   `IBrailleDisplayController.h`: The abstract C++ interface.
    *   `BpBrailleDisplayController.h`/`.cpp`: The proxy class that the system server will use to make calls.
    *   `BnBrailleDisplayController.h`/`.cpp`: The stub base class. The service's `BrailleDisplayControllerImpl` C++ equivalent will contain an inner class that inherits from this stub.
*   **`byte[]`**: The C++ equivalent for `in byte[]` is `const std::vector<uint8_t>&`.
*   **Usage**: The C++ `BrailleDisplayControllerImpl` would create an instance of its `BnBrailleDisplayController` implementation and pass its `asBinder()` token to the system during the `connect` call. The methods of this stub would be responsible for posting tasks to the service's main event loop to execute the user's C++ `BrailleDisplayCallback`.

## Implementation Risks
*   **Thread Handling**: The calls on this interface will arrive in the service's process on a background Binder thread. The implementation *must* delegate the work to the appropriate application thread (e.g., via an event loop) before invoking any user-provided callbacks. The Java implementation (`BrailleDisplayControllerImpl.IBrailleDisplayControllerWrapper`) does this correctly using an `Executor`. A C++ version must do the same.
*   **Binder Identity**: As with all system-to-app callbacks, the implementation should clear the calling identity before executing user code to avoid letting the app inherit the system's permissions. The Java implementation does this with `Binder.clearCallingIdentity()`; the C++ version should use `IPCThreadState::clearCallingIdentity()`.

## Questions for C++ Team
*   What is the C++ class that will be responsible for inheriting from `BnBrailleDisplayController`?
*   How will the `IBrailleDisplayConnection` proxy object, received in `onConnected`, be managed to ensure its lifecycle is handled correctly? (e.g., using `std::shared_ptr`).
