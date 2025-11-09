# BrailleDisplayController - Reverse Engineering Documentation

## Executive Summary
This document provides a detailed analysis of the Java `BrailleDisplayController` interface. This interface defines a contract for communicating with a Braille display that adheres to the Human Interface Device (HID) standard over USB or Bluetooth. Its primary purpose is to allow an Android Accessibility Service to connect to, send output to, and receive input from a single Braille display device at a time.

The design is asynchronous and callback-driven. The client initiates a connection to a specific device and provides a callback object to handle events like successful connection, connection failure, data input, and disconnection.

## Architecture Overview
The architecture is based on the **Strategy** and **Observer** design patterns.

*   **`BrailleDisplayController` (Interface/Strategy)**: This is a pure interface (`interface` in Java, abstract base class in C++) that defines the API for interacting with a Braille display. The concrete implementation is provided by the Android system, abstracting the details of Bluetooth/USB communication.
*   **`BrailleDisplayCallback` (Observer)**: This nested interface defines the contract for an object that receives asynchronous notifications from the `BrailleDisplayController`. The client of the controller must implement this interface to handle connection events and incoming data.

The flow is as follows:
1.  The client (an Accessibility Service) obtains an instance of the `BrailleDisplayController`.
2.  The client implements the `BrailleDisplayCallback` interface.
3.  The client calls one of the `connect` methods, passing a device object (Bluetooth or USB) and its callback implementation.
4.  The system attempts the connection asynchronously.
5.  The system invokes methods on the provided `BrailleDisplayCallback` instance to report the outcome (`onConnected`, `onConnectionFailed`).
6.  Once connected, the client can `write` data, and the system will call `onInput` when data is received.
7.  The connection can be terminated by the client (`disconnect`) or by the system (e.g., device unplugged), which triggers the `onDisconnected` callback.

This entire feature is gated by a system flag, `Flags.FLAG_BRAILLE_DISPLAY_HID`. Any attempt to use the API when the flag is disabled will result in an `IllegalStateException`.

## Detailed Functionality

### Feature: Connection Management
*   **Purpose**: To establish and terminate a connection to a Braille display.
*   **Algorithm**:
    1.  **Connection Request**: The client calls `connect()` with a `BluetoothDevice` or `UsbDevice` object and a `BrailleDisplayCallback`. An optional `Executor` can be provided to control the callback thread.
    2.  **Precondition Checks**: The system checks:
        *   If a device is already connected. If so, throw `IllegalStateException`.
        *   If the required permissions are held (`BLUETOOTH_CONNECT` for Bluetooth, prior `UsbManager` approval for USB). If not, throw `SecurityException`.
    3.  **Asynchronous Connection**: The system initiates the connection to the physical device.
    4.  **Outcome Notification**:
        *   **On Success**: The system retrieves the HID report descriptor from the device and invokes `BrailleDisplayCallback.onConnected()` with the descriptor. It then begins listening for input.
        *   **On Failure**: The system invokes `BrailleDisplayCallback.onConnectionFailed()` with a bitmask of error codes.
    5.  **Disconnection**:
        *   The client calls `disconnect()` to manually terminate the session.
        *   If the system detects a problem (e.g., device unplugged, I/O error), it closes the connection and invokes `BrailleDisplayCallback.onDisconnected()`.

*   **Java-Specific Notes**:
    *   The use of `@RequiresPermission` is a compile-time and runtime check enforced by the Android framework.
    *   The `Executor` pattern is a standard Java concurrency feature for defining where to run a task. The default is the service's main thread executor.

*   **C++ Implementation Guidance**:
    *   The `connect` methods should be asynchronous, returning immediately. The connection logic should run on a background thread.
    *   The callback `Executor` can be implemented using `std::function<void(std::function<void()>)>`. This allows the client to provide a lambda or function object that queues the actual callback for execution on the desired thread (e.g., a GUI thread message loop, a thread pool).
    *   Permissions checks must be handled by the C++ environment's context. The implementation should assume the caller has the necessary permissions.

### Feature: Data I/O
*   **Purpose**: To send data to and receive data from the connected Braille display.
*   **Algorithm**:
    1.  **Writing Data**:
        *   The client calls `write()` with a byte buffer.
        *   The system checks if a device is connected. If not, throw `IOException`.
        *   The system checks if the buffer size exceeds the IPC limit. If so, throw `IllegalArgumentException`.
        *   The system queues the buffer to be sent to the device. This is an asynchronous "fire and forget" operation from the client's perspective. Errors in the actual write are handled by disconnecting the device.
    2.  **Reading Data**:
        *   An internal system thread continuously listens for input from the connected device.
        *   When input bytes are received, the system packages them into a byte array.
        *   The system invokes `BrailleDisplayCallback.onInput()` with the received data, using the specified `Executor`.

*   **Java-Specific Notes**:
    *   The `byte[]` is a primitive Java array.
    *   `IOException` is a checked exception in Java, signaling I/O failures.
    *   The mention of `IBinder.getSuggestedMaxIpcSizeBytes()` reveals this is implemented over Android's Binder IPC mechanism.

*   **C++ Implementation Guidance**:
    *   Use `std::vector<uint8_t>` for byte buffers.
    *   The `write` method should throw exceptions analogous to the Java ones: a logic error for writing when disconnected, and a length error for oversized buffers.
    *   A dedicated reader thread is required to listen for input and dispatch it via the callback mechanism. This thread must be carefully managed to ensure it is terminated when the device is disconnected.

## Data Model

| Java Type                  | C++ Equivalent                                | Notes                                                                                                                              |
| -------------------------- | --------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| `BrailleDisplayController` | `class BrailleDisplayController` (Abstract)   | Pure virtual interface.                                                                                                            |
| `BrailleDisplayCallback`   | `class BrailleDisplayCallback` (Abstract)     | Pure virtual interface for observer callbacks.                                                                                     |
| `byte[]`                   | `std::vector<uint8_t>`                        | Represents HID descriptors and I/O buffers.                                                                                      |
| `BluetoothDevice`          | `struct BluetoothDeviceHandle` or `void*`     | Opaque handle or custom struct representing the device. The C++ environment needs a way to identify system Bluetooth devices.    |
| `UsbDevice`                | `struct UsbDeviceHandle` or `void*`           | Opaque handle or custom struct representing the device.                                                                          |
| `Executor`                 | `std::function<void(std::function<void()>)>`  | A function that takes a task (another function) and executes it.                                                                 |
| `@ErrorCode int` flags     | `enum class ErrorCode : uint32_t` with bitwise operators | `FLAG_ERROR_CANNOT_ACCESS = 1 << 0`, `FLAG_ERROR_BRAILLE_DISPLAY_NOT_FOUND = 1 << 1`. Use a typesafe enum with bitmasking. |

## API Reference

### Interface `BrailleDisplayController`

**Methods**

*   `void connect(@NonNull BluetoothDevice bluetoothDevice, @NonNull BrailleDisplayCallback callback)`
*   `void connect(@NonNull BluetoothDevice bluetoothDevice, @NonNull @CallbackExecutor Executor callbackExecutor, @NonNull BrailleDisplayCallback callback)`
    *   **Purpose**: Connects to a Bluetooth Braille display.
    *   **Parameters**:
        *   `bluetoothDevice`: A handle to the target device.
        *   `callbackExecutor`: (Optional) The executor on which to run callbacks. If not provided, a default main-thread executor is assumed.
        *   `callback`: The object that will receive connection events.
    *   **Preconditions**:
        *   The feature flag `braille_display_hid` must be enabled.
        *   `isConnected()` must be `false`.
        *   Caller must have the `android.Manifest.permission.BLUETOOTH_CONNECT` permission.
    *   **Postconditions**: The connection process is initiated. One of the `callback` methods (`onConnected` or `onConnectionFailed`) will be invoked asynchronously.
    *   **Throws**: `IllegalStateException` if already connected.

*   `void connect(@NonNull UsbDevice usbDevice, @NonNull BrailleDisplayCallback callback)`
*   `void connect(@NonNull UsbDevice usbDevice, @NonNull @CallbackExecutor Executor callbackExecutor, @NonNull BrailleDisplayCallback callback)`
    *   **Purpose**: Connects to a USB Braille display.
    *   **Preconditions**:
        *   Same as Bluetooth `connect`, plus the application must have been granted permission to access the `UsbDevice` via `UsbManager`.
    *   **Throws**: `IllegalStateException` if already connected, `SecurityException` if USB permission is not granted.

*   `boolean isConnected()`
    *   **Purpose**: Checks if a Braille display is currently connected.
    *   **Returns**: `true` if connected, `false` otherwise.
    *   **Thread Safety**: Must be thread-safe.

*   `void write(@NonNull byte[] buffer) throws IOException`
    *   **Purpose**: Sends an output report to the connected device.
    *   **Parameters**: `buffer` - The HID report bytes to send.
    *   **Preconditions**: `isConnected()` must be `true`.
    *   **Throws**:
        *   `IOException` (in C++, a `std::runtime_error` or similar) if not connected.
        *   `IllegalArgumentException` (in C++, `std::invalid_argument` or `std::length_error`) if `buffer.length` exceeds the IPC limit.

*   `void disconnect()`
    *   **Purpose**: Disconnects from the current device. If no device is connected, this method does nothing. If a connection is in progress, it should be cancelled.
    *   **Postconditions**: If a device was connected, `onDisconnected` will eventually be called on the callback. The controller will be in a disconnected state.

---

### Interface `BrailleDisplayCallback`

**Methods**

*   `void onConnected(@NonNull byte[] hidDescriptor)`
    *   **Purpose**: Called when a connection is successfully established.
    *   **Parameters**: `hidDescriptor` - The raw HID Report Descriptor from the device. The client uses this to parse incoming reports and format outgoing reports.

*   `void onConnectionFailed(@ErrorCode int errorFlags)`
    *   **Purpose**: Called when a connection attempt fails.
    *   **Parameters**: `errorFlags` - A bitmask of `ErrorCode` flags indicating the reason for failure.

*   `void onInput(@NonNull byte[] input)`
    *   **Purpose**: Called when an input report is received from the device.
    *   **Parameters**: `input` - The raw input bytes from the device.

*   `void onDisconnected()`
    *   **Purpose**: Called when the device is disconnected, either by a call to `disconnect()` or by the system due to an error or the device being unplugged.

## Java-to-C++ Translation Guide

| Java Feature/Concept         | C++ Equivalent/Strategy                                                                                                             |
| ---------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| **Interface**                | Abstract base class with pure virtual methods (`virtual void foo() = 0;`).                                                          |
| **`@NonNull` Annotation**    | Use references (`T&`) or pointers (`T*`) with `assert(ptr != nullptr)` checks. For owned objects passed as parameters, `std::unique_ptr<T>`. |
| **`Executor`**               | `std::function<void(std::function<void()>)>`. The C++ client provides a function that schedules a task on the correct thread.       |
| **`byte[]`**                 | `std::vector<uint8_t>`. Use `const std::vector<uint8_t>&` for input parameters and `std::vector<uint8_t>` for ownership.             |
| **Exception Handling**       | Define a hierarchy of C++ exceptions (e.g., `struct IOException : std::runtime_error {}`) or use `std::system_error` with error codes. The choice should be consistent with the target C++ project's conventions. |
| **`IllegalStateException`**  | `std::logic_error`. Represents a call made at an inappropriate time.                                                                |
| **`SecurityException`**      | Custom exception type (e.g., `SecurityError`) deriving from `std::runtime_error`.                                                   |
| **`@FlaggedApi`**            | The C++ implementation should be wrapped in a similar feature flag check. A global function `bool isBrailleDisplayHidEnabled()` could be used at API entry points, throwing an exception if it returns false. |
| **Memory Management (GC)**   | The C++ implementation must use explicit memory management. Use RAII, `std::unique_ptr`, and `std::shared_ptr` to manage object lifetimes. The comment `SuppressLint("NotCloseable")` implies the system manages the underlying connection resource, so the C++ controller class might just hold a non-owning handle. `disconnect()` signals the system to release the resource. |
| **Concurrency**              | Use `std::mutex` to protect shared state like the `isConnected` flag. The reader thread for `onInput` must be managed with `std::thread` and `std::jthread` (C++20) and safely terminated on disconnection. |

## Test Cases & Validation

The C++ implementation should be validated against the following scenarios:

1.  **Happy Path (Bluetooth)**:
    *   Input: `connect(valid_bt_device, callback)`
    *   Expected: `callback.onConnected` is called with a valid HID descriptor. `isConnected()` returns `true`.
2.  **Happy Path (USB)**:
    *   Input: `connect(valid_usb_device, callback)`
    *   Expected: `callback.onConnected` is called. `isConnected()` returns `true`.
3.  **Connection Failure**:
    *   Input: `connect(nonexistent_device, callback)`
    *   Expected: `callback.onConnectionFailed` is called with `FLAG_ERROR_BRAILLE_DISPLAY_NOT_FOUND`.
4.  **Connect When Already Connected**:
    *   Input: `connect(...)` -> `onConnected` -> `connect(...)` again.
    *   Expected: Second `connect` call throws `std::logic_error`.
5.  **Write Data**:
    *   Input: After connection, `write({0x01, 0x02, 0x03})`.
    *   Expected: Method returns without error. Data is sent to the device.
6.  **Write When Disconnected**:
    *   Input: `write(...)` before connecting or after disconnecting.
    *   Expected: Method throws `IOException` equivalent.
7.  **Input Received**:
    *   Precondition: A connected device sends data.
    *   Expected: `callback.onInput` is called with the data bytes on the correct executor thread.
8.  **Manual Disconnect**:
    *   Input: `connect(...)` -> `onConnected` -> `disconnect()`.
    *   Expected: `callback.onDisconnected` is called. `isConnected()` returns `false`.
9.  **System-Initiated Disconnect**:
    *   Precondition: Device is physically unplugged while connected.
    *   Expected: `callback.onDisconnected` is called. `isConnected()` returns `false`.

## Implementation Risks

1.  **Threading Complexity**: The executor model requires careful implementation to avoid race conditions and ensure callbacks are correctly marshaled to the client's desired thread. Incorrect synchronization could lead to deadlocks or corrupted state.
2.  **Resource Management**: The underlying connection is managed by the system. The C++ object must correctly interface with the system's lifecycle hooks to avoid leaking resources or attempting to use a stale connection handle. The RAII pattern must be applied carefully.
3.  **IPC Buffer Limits**: The check for the buffer size in `write()` is critical. The C++ implementation must know the equivalent IPC buffer limit in its environment and enforce it to prevent crashes.
4.  **Platform Abstraction**: The code interacts with specific platform features (`BluetoothDevice`, `UsbDevice`, system permissions). The C++ implementation will require a robust platform abstraction layer to represent these concepts.

## Questions for C++ Team

1.  **Error Handling Strategy**: Should the C++ API use exceptions, `std::expected` (C++23), or return codes to report errors? The Java interface uses exceptions.
2.  **Threading Model**: What is the standard threading model for callbacks in the target C++ environment? Is there an existing "main thread" or event loop to post tasks to, or should we provide a more generic `Executor` model?
3.  **Device Representation**: How are Bluetooth and USB devices represented at the C++ level? Are there existing wrappers or handle types we should use?
4.  **Feature Flag Mechanism**: How are system-level feature flags checked in the C++ environment? We need a C++ equivalent of `Flags.brailleDisplayHid()`.