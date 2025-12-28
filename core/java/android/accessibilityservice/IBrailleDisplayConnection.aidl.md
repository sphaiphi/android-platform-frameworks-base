
# IBrailleDisplayConnection.aidl - Reverse Engineering Documentation

## Executive Summary
`IBrailleDisplayConnection` is a one-way AIDL interface that defines the communication channel from an accessibility service *to* the system server for an active Braille display connection. It provides the methods that the service's `BrailleDisplayController` can call to interact with the connected device.

## Architecture Overview
*   **Service-to-System Communication**: This interface represents the "write" channel for a Braille display. Once a connection is established (via `IAccessibilityServiceConnection`), the system server returns a Binder object implementing this interface to the service. The service then uses this object to send commands.
*   **One-Way Methods**: Both methods are implicitly `oneway` because the interface is not declared `oneway`, but the methods have no return values. This means when a service calls `write()` or `disconnect()`, the call returns immediately without waiting for the system server to complete the action. This is a "fire-and-forget" model, suitable for sending output data that doesn't require an immediate response.
*   **Paired Interface**: This interface is paired with `IBrailleDisplayController.aidl`. `IBrailleDisplayConnection` is for service-to-system calls, while `IBrailleDisplayController` is for system-to-service callbacks. Together they form the bidirectional communication link for a Braille display session.

## Detailed Functionality

### `disconnect()`
*   **Purpose**: To command the system server to terminate the current Braille display connection.
*   **Algorithm**: The client (the accessibility service) calls this method. The system server receives the call and proceeds to close the underlying HID device connection and clean up associated resources. Because it's a `oneway` call, the service does not wait for confirmation. The confirmation of disconnection comes asynchronously via the `IBrailleDisplayController.onDisconnected()` callback.

### `write(in byte[] output)`
*   **Purpose**: To send an output report (data) to the Braille display.
*   **Algorithm**: The client calls this method with a byte array containing the HID output report. The system server receives this data and writes it to the appropriate HID device file (e.g., `/dev/hidrawX`).
*   **`in` keyword**: This keyword is an optimization indicating that the `byte[]` is only being sent from the client to the server, and no data needs to be copied back in the reply `Parcel`.

## Java-to-C++ Translation Guide
*   **Binder Interface Generation**: The AIDL compiler will generate the corresponding C++ files:
    *   `IBrailleDisplayConnection.h`: The abstract C++ interface.
    *   `BpBrailleDisplayConnection.h`/`.cpp`: The proxy class that a C++ accessibility service will hold and use to make calls.
    *   `BnBrailleDisplayConnection.h`/`.cpp`: The stub base class that the system server's connection object will implement.
*   **`byte[]`**: The C++ equivalent for `in byte[]` is typically `const std::vector<uint8_t>&`. The Binder framework will handle the serialization.
*   **Usage**: A C++ `BrailleDisplayController` implementation would hold a `std::shared_ptr<IBrailleDisplayConnection>` (the `Bp` proxy) and call its `disconnect()` and `write()` methods.

## Implementation Risks
*   **Error Handling**: Because the methods are `oneway`, there is no immediate feedback if a `write` or `disconnect` operation fails at the system level. The only notification of a failure is an asynchronous `onDisconnected()` callback. The client code must be robust enough to handle this asynchronous error model and not assume that a call to `write` guarantees successful delivery.
*   **Data Integrity**: The `write` method sends raw bytes. It is the client's responsibility to ensure that the byte array is a correctly formatted HID output report according to the device's HID descriptor. Sending malformed data could cause the device to behave incorrectly.

## Questions for C++ Team
*   How will the `BpBrailleDisplayConnection` proxy object be passed from the system to the C++ service during the connection setup? (This corresponds to the `onConnected` callback in `IBrailleDisplayController`).
*   What is the C++ strategy for handling the asynchronous nature of errors on this interface?
