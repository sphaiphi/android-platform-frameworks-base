# LegacyMessageQueue - Reverse Engineering Documentation

## Executive Summary
`LegacyMessageQueue` implements the traditional Android message dispatch loop. It manages a prioritized list of `Message` objects, handles synchronization barriers, dispatching `IdleHandler` callbacks when the queue is empty, and monitoring file descriptors for I/O events. It relies on native code (`nativePollOnce`, `nativeWake`) to efficiently block the thread when no work is pending.

## Architecture Overview
-   **Core Pattern**: Event Loop / Message Pump.
-   **Components**:
    -   `MessageQueue`: The main orchestrator.
    -   `Message`: A linked-list node representing a task or data to process.
    -   `IdleHandler`: Callback interface for tasks to run when the thread is idle.
    -   `FileDescriptorRecord`: Listener for native file descriptor events (input/output/error).
-   **Native Integration**: Uses JNI for low-level waiting (epoll) and waking.

## Detailed Functionality

### Message Dispatching
-   **`next()`**: The core loop method.
    -   Calls `nativePollOnce(ptr, timeout)` to sleep until a message is due or an event occurs.
    -   Wakes up and checks the head of the `mMessages` linked list.
    -   **Sync Barriers**: If the head message has a `null` target, it's a barrier. The queue searches for the next *asynchronous* message, skipping synchronous ones.
    -   **Timing**: If the message timestamp (`when`) is in the future, it calculates the next timeout duration.
    -   **Idle Handling**: If no messages are ready, it executes registered `IdleHandler`s.

### Enqueuing (`enqueueMessage`)
-   **Insertion**: Messages are inserted into the linked list sorted by their `when` timestamp.
-   **Wakeup**: If the new message is inserted at the head of the queue (or before the currently pending message), `nativeWake(mPtr)` is called to unblock `next()`.

### Synchronization Barriers
-   **Purpose**: To block "synchronous" messages (like UI layout/traversal) while allowing "asynchronous" messages (like vsync signals or input events) to proceed. Used heavily by the View system.
-   **Mechanism**: A message with `target == null` acts as a barrier.
-   **API**: `postSyncBarrier()` / `removeSyncBarrier(token)`.

### File Descriptor Monitoring
-   **`addOnFileDescriptorEventListener`**: Registers a callback for FD events (Read/Write/Error).
-   **Native Mapping**: Calls `nativeSetFileDescriptorEvents`. When the native loop wakes up due to an FD event, it calls `dispatchEvents` back into Java.

## Data Model
-   **`mMessages`**: Head of the singly-linked list of `Message` objects.
-   **`mIdleHandlers`**: ArrayList of idle callbacks.
-   **`mFileDescriptorRecords`**: SparseArray mapping FD integers to listener records.

## API Reference
-   `next()`: Retrieve next message (blocking).
-   `enqueueMessage(Message, long)`: Add message.
-   `add/removeIdleHandler(IdleHandler)`: Manage idle callbacks.
-   `post/removeSyncBarrier(...)`: Manage dispatch barriers.
-   `add/removeOnFileDescriptorEventListener(...)`: Manage FD listeners.

## Java-to-C++ Translation Guide
-   **Native Loop**: The core blocking logic is already native (`Looper.cpp` / `MessageQueue.cpp` in frameworks/native).
-   **Translation Strategy**:
    -   If implementing a pure C++ Looper, rely on `android::Looper` and `android::SimpleLooper` (NDK).
    -   The linked-list management of *Java objects* (`Message`) must be replicated if porting the *Queue* logic specifically, but typically C++ loopers manage `struct Message` or similar payloads directly.
    -   **Barriers**: Standard C++ Loopers don't always have the exact "Sync Barrier" semantics of Android's Java queue (blocking specific message types). This logic is specific to the Android UI thread requirements.

## Implementation Risks
-   **Sync Barriers**: Improper handling (e.g., posting a barrier and never removing it) effectively freezes the UI thread for standard messages.
-   **Concurrency**: All list modifications are guarded by `synchronized(this)`. Any C++ port must use `std::mutex` equivalents rigorously.
