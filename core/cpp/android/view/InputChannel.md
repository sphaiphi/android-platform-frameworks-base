# InputChannel - Reverse Engineering Documentation

## Executive Summary
`InputChannel` is a Parcelable object that encapsulates a communication pipe (using a Unix domain socket) used to transmit input events between the system's `InputDispatcher` and an application process. It ensures that input events are delivered reliably and efficiently across process boundaries.

## Architecture Overview
*   **Role**: IPC transport for input events.
*   **Mechanism**: Uses a socket-based protocol. One end is held by the dispatcher (Server), the other by the app (Client).
*   **Threading**: Only one thread should read from an `InputChannel` at a time.

## Detailed Functionality

### 1. Channel Pairs
*   **`openInputChannelPair()`**: A static method that creates a two-way pipe.

### 2. Lifecycle
*   **`dispose()`**: Closes the communication pipe and releases native resources.
*   **`dup()`**: Creates a copy of the channel handle (for sharing between threads/processes).

### 3. Identity
*   **`getToken()`**: Returns the `IBinder` associated with the channel, used for matching events to windows.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::InputChannel`.
*   **Parceling**: Serializes the file descriptor of the underlying socket. C++ code must use `Parcel::writeDupFileDescriptor`.

## Implementation Risks
*   **Deadlock**: Blocking the thread that reads from an `InputChannel` will stop all input processing for that window and eventually trigger an ANR.
*   **Resource Exhaustion**: Each channel consumes a file descriptor. Failing to `dispose()` channels can lead to the process hitting the FD limit.
