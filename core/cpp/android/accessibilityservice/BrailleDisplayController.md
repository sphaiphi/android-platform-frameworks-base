
# BrailleDisplayController - Reverse Engineering Documentation

## Executive Summary
`BrailleDisplayController` is a Java interface that defines the API for an `AccessibilityService` to communicate with a hardware Braille display. It supports connecting to a device, writing data to it, reading data from it, and disconnecting. The interface is designed to work with Braille displays that adhere to the HID (Human Interface Device) standard over Bluetooth or USB.

## Architecture Overview
*   **Interface-based API**: This is a pure interface, defining a contract for a controller object that will be provided to accessibility services. The actual implementation (`BrailleDisplayControllerImpl`) is hidden from the public API.
*   **Asynchronous Connection**: The `connect()` methods are asynchronous. The caller provides a `BrailleDisplayCallback` object, and the result of the connection attempt (success or failure) is delivered to the methods of that callback (`onConnected`, `onConnectionFailed`).
*   **Callback-driven Input**: Once connected, incoming data from the Braille display is not read via a blocking `read()` call. Instead, the system listens for input and pushes it to the service via the `BrailleDisplayCallback.onInput()` method. This is an event-driven model.
*   **Feature Flagging**: The entire API is guarded by the `Flags.FLAG_BRAILLE_DISPLAY_HID` feature flag. A static method `checkApiFlagIsEnabled()` throws an exception if the feature is not enabled on the system, preventing the API from being used.

## Detailed Functionality

### `connect(...)` Methods
*   **Purpose**: To initiate a connection to a Braille display.
*   **Overloads**: There are separate methods for connecting to a `BluetoothDevice` and a `UsbDevice`. Each of these has a further overload that allows specifying a custom `Executor` for callbacks to run on.
*   **Algorithm**:
    1.  Check if the feature flag is enabled.
    2.  Check if a device is already connected. If so, throw `IllegalStateException`.
    3.  Make an IPC call to the system server to establish the connection.
    4.  The system server handles the low-level HID communication.
    5.  The result is delivered asynchronously to the provided `BrailleDisplayCallback`.
*   **Java-Specific Notes**: Uses `Executor` for flexible callback threading.
*   **C++ Implementation Guidance**: The C++ interface would have similar `connect` methods. The `Executor` could be replaced with a C++ equivalent, such as a reference to a thread pool or an event queue. The `BluetoothDevice` and `UsbDevice` would be replaced by C++ objects representing those devices (e.g., holding an address or file descriptor).

### `write(byte[] buffer)`
*   **Purpose**: To send data (a HID report) to the connected Braille display.
*   **Algorithm**:
    1.  Performs checks for connection status and buffer size.
    2.  Makes an IPC call to the system server, passing the byte array.
    3.  The system server writes the data to the underlying HID device.
*   **Exception Handling**: Throws `IOException` if not connected and `IllegalArgumentException` if the buffer is too large for IPC.
*   **C++ Implementation Guidance**: A `write(const std::vector<uint8_t>& buffer)` method would be the C++ equivalent. It would throw C++ exceptions (`std::runtime_error`, `std::invalid_argument`) under the same conditions.

### `disconnect()`
*   **Purpose**: To terminate the connection with the Braille display.
*   **Algorithm**: Makes an IPC call to the system server to close the connection and release resources.

### `BrailleDisplayCallback` Nested Interface
This interface defines the contract for receiving events from the controller.
*   **`onConnected(byte[] hidDescriptor)`**: Called on successful connection. It crucially provides the HID Report Descriptor, which is essential for parsing incoming data from `onInput` and formatting outgoing data for `write`.
*   **`onConnectionFailed(int errorFlags)`**: Called if the connection fails, with flags indicating the reason.
*   **`onInput(byte[] input)`**: Called whenever new data arrives from the Braille display.
*   **`onDisconnected()`**: Called when the device is disconnected, either by request (`disconnect()`) or unexpectedly (e.g., unplugged).

## Data Model
This is an interface and has no data members itself. The implementing class (`BrailleDisplayControllerImpl`) would hold:
*   A reference to the accessibility service.
*   A Binder proxy to the system service (`IAccessibilityServiceConnection`).
*   A reference to the active connection object (`IBrailleDisplayConnection`).
*   The user-provided `BrailleDisplayCallback` and `Executor`.
*   A lock for thread synchronization.

## Java-to-C++ Translation Guide
*   **Interface**: The `BrailleDisplayController` and `BrailleDisplayCallback` would be defined as abstract base classes in C++.
*   **Feature Flag**: The `checkApiFlagIsEnabled` logic would need to be replicated, likely by checking a system property or a compile-time flag in C++.
*   **`byte[]`**: C++ can use `std::vector<uint8_t>` or `gsl::span<uint8_t>` to represent byte buffers.
*   **Permissions**: The `@RequiresPermission` annotations are enforced at the Android system level. A C++ implementation running in a different context would need its own permission model.
*   **IPC**: The entire implementation relies on Binder IPC to a system service that manages the low-level device communication. A C++ version would need a corresponding C++ Binder service and client infrastructure.

## Implementation Risks
*   **Low-Level HID Handling**: The core complexity is hidden in the system server, which manages the HIDRAW or Bluetooth L2CAP connections. A full reimplementation would need to handle all the intricacies of low-level device I/O.
*   **Asynchronous Race Conditions**: The asynchronous nature of `connect` and `disconnect` requires careful state management to avoid race conditions. For example, a call to `write` could come in while a `disconnect` is in progress. The implementation must handle this gracefully.
*   **Callback Lifetime**: The C++ implementation must safely manage the lifetime of the `BrailleDisplayCallback` pointer or reference to avoid use-after-free errors. Using `std::shared_ptr` or a similar mechanism is advisable.

## Questions for C++ Team
*   What is the C++ equivalent for representing Bluetooth and USB devices that will be passed to the `connect` methods?
*   What is the expected C++ threading model for callbacks? Should we use a specific event loop library?
*   How will HID-level communication be handled in the C++ environment? Will we be implementing this from scratch or using an existing library?
