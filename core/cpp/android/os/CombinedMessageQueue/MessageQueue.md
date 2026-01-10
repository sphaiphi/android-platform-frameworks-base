# CombinedMessageQueue - Reverse Engineering Documentation

## Executive Summary
`MessageQueue` is the fundamental mechanism for dispatching messages and runnables to a `Looper`. This specific implementation, "CombinedMessageQueue", is a hybrid that selects between a **Legacy** (locked linked-list) implementation and a **Concurrent** (lock-free/fine-grained locked) implementation at runtime. This selection is based on process type (system vs. app) and flags (`Flags.forceConcurrentMessageQueue()`). It handles the core event loop logic: enqueueing messages, retrieving the next message (with blocking), and managing synchronization barriers and idle handlers.

## Architecture Overview
-   **Pattern**: Strategy / Toggle
-   **Core Components**:
    -   `MessageQueue`: The public facade. Contains logic to choose between `Legacy` and `Concurrent` paths for every operation.
    -   **Legacy Path**: Uses a single `synchronized(this)` lock and a singly-linked list (`Message mMessages`) to store messages.
    -   **Concurrent Path**: Uses more complex data structures (implied `MessageNode`, priority queues, stack) and `ReentrantLock` (`mDrainingLock`) to allow higher concurrency and throughput.
-   **Native Integration**: Heavily relies on JNI (`nativePollOnce`, `nativeWake`) to block the thread when idle and wake it when new work arrives or IO events occur.

## Detailed Functionality

### Mode Selection (`initIsProcessAllowedToUseConcurrent`)
-   Determines `mUseConcurrent` at construction.
-   **Criteria**:
    -   False if `Flags.messageQueueForceLegacy()` is true.
    -   False if `Process.myProcessName()` is null (host-side tests).
    -   True if `Flags.forceConcurrentMessageQueue()` is true (unless Robolectric).
    -   Defaults to `UserHandle.isCore(Process.myUid())` (System processes) but excludes processes with "test" in the name to avoid breaking reflection-based tests.

### Message Enqueueing (`enqueueMessage`)
-   **Legacy**:
    -   Locks `this`.
    -   Inserts `Message` into the linked list sorted by `when` timestamp.
    -   Wakes native looper if the new message is at the head or effectively changes the sleep time.
-   **Concurrent**:
    -   Delegates to `enqueueMessageConcurrent` (implied complex logic, potentially lock-free or using fine-grained locks, though specific implementation details of `enqueueMessageUnchecked` are deeper in the file).

### Message Retrieval (`next`)
-   **Legacy (`nextLegacy`)**:
    -   Calls `nativePollOnce(ptr, timeout)`.
    -   Locks `this`.
    -   Traverses list. Handles **Sync Barriers** (messages with `target==null`) by searching for the first `isAsynchronous()` message.
    -   Returns message if `now >= msg.when`.
    -   Calculates next timeout if not ready.
    -   Runs `IdleHandler`s if queue is empty or head is in future.
-   **Concurrent (`nextConcurrent`)**:
    -   Loops calling `nativePollOnce`.
    -   Calls `nextMessage(false, false)` to retrieve from internal structures.
    -   Manages `IdleHandler`s similarly but using `mIdleHandlersLock`.

### Synchronization Barriers (`postSyncBarrier`, `removeSyncBarrier`)
-   **Concept**: A "null target" message that effectively pauses processing of *synchronous* messages. Only *asynchronous* messages are processed until the barrier is removed.
-   **Legacy**: Inserts a message with `target=null` into the linked list.
-   **Concurrent**: Uses `mNextBarrierTokenAtomic` and specific logic to handle barriers in the priority queue.

### Idle Handlers
-   Listeners registered to run when the queue is about to block (waiting for more work).
-   Stored in `ArrayList<IdleHandler>`.
-   **Legacy**: Protected by `synchronized(this)`.
-   **Concurrent**: Protected by `synchronized(mIdleHandlersLock)`.

### File Descriptor Events
-   Allows registering callbacks for FD events (Input, Output, Error) via `nativeSetFileDescriptorEvents`.
-   **dispatchEvents**: Called from native code when an event occurs. Delegates to the registered `OnFileDescriptorEventListener`.

## Data Model

### Key Fields
-   `mPtr` (long): Pointer to native `MessageQueue` object.
-   `mMessages` (Message): **Legacy only**. Head of the linked list.
-   `mIdleHandlers` (ArrayList): List of idle callbacks.
-   `mFileDescriptorRecords` (SparseArray): Map of FD number to listener record.
-   `mUseConcurrent` (boolean): The toggle switch.

### Helper Classes
-   `MessageNode` (Concurrent only): Wrapper for `Message` in the concurrent structures.
-   `StackNode`, `StateNode` (Concurrent only): Used for managing the lock-free/concurrent stack state.
-   `MessageCompare` (Abstract): Strategy for finding/removing messages matching specific criteria (Concurrent only).

## API Reference
-   `next()`: Retrieve next message (blocks).
-   `enqueueMessage(Message, long)`: Add message.
-   `removeMessages(Handler, ...)`: Remove specific messages.
-   `addIdleHandler(IdleHandler)`: Add idle callback.
-   `addOnFileDescriptorEventListener(...)`: Watch a raw FD.
-   `postSyncBarrier()`: Block sync messages.
-   `removeSyncBarrier(int)`: Unblock sync messages.
-   `isIdle()`: Check if queue is empty/waiting.

## Java-to-C++ Translation Guide

### Architecture
-   **Native Looper**: Android already has a C++ `Looper` and `MessageQueue` (`libutils`/`libstagefright` or `ALooper`). This Java class is effectively a wrapper around that native machinery but *also* implements the message linked-list logic in Java.
-   **Translation Strategy**:
    -   If implementing a pure C++ Looper: Use `ALooper` (NDK) or `android::Looper` (framework native).
    -   `android::Looper` already handles `pollOnce`, `wake`, and FD monitoring.
    -   The *Java Message List* logic (`next`, `enqueueMessage`) is usually implemented in C++ by `android::Looper` having a `sendMessage` that pushes to a C++ list.
    -   **Crucial Difference**: Android's Java `MessageQueue` keeps the *messages* in Java heap. The Native `MessageQueue` (C++) only handles the *waking* mechanism and FD events.
    -   **Re-implementation**: You will need a C++ `std::priority_queue` or sorted `std::list` of `Message` objects.

### Specific Mappings
| Java | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `nativePollOnce` | `Looper::pollOnce` | Blocks on `epoll`. |
| `nativeWake` | `Looper::wake` | Writes to eventfd/pipe to wake `epoll`. |
| `Message` | `struct Message` | Needs `what`, `arg1`, `arg2`, `obj`, `when`. |
| `Handler` | `sp<MessageHandler>` | Callback interface. |
| `IdleHandler` | `sp<LooperCallback>` | C++ Looper has similar mechanism. |
| `FileDescriptorRecord` | `Looper::addFd` | Native Looper supports FD listeners directly. |
| `postSyncBarrier` | Custom Logic | Native Looper doesn't natively support "Barriers" in the generic sense; you'd implement this in your dispatch loop. |

### Concurrency
-   The "Combined" nature implies specialized high-performance needs for the System Server. For a general C++ port, the **Legacy** (mutex-protected list) model is sufficient and standard for `android::Looper`.
-   **Locking**: `std::mutex` + `std::unique_lock`. `std::condition_variable` is implicitly handled by the `epoll` mechanism in `Looper::pollOnce`.

## Implementation Risks
-   **Reflection Compatibility**: The Java code goes to great lengths (Legacy fallback) to support tests that use reflection on `mMessages`. A C++ rewrite breaks this entirely for Java callers (obviously).
-   **Sync Barriers**: This is a subtle feature used heavily by the View system (waiting for VSYNC). Correct implementation is critical for UI responsiveness.
-   **JNI Boundary**: The existing class crosses JNI boundaries for *every* poll. A pure C++ implementation avoids this overhead.

## Questions for C++ Team
1.  Are we porting the *logic* of the Java MessageQueue to C++, or are we wrapping the existing C++ `android::Looper`? (Likely the latter, as it's the foundation).
2.  Do we need the "Concurrent" complexity? `android::Looper` is traditionally single-threaded dispatch (per Looper), thread-safe enqueue. The "Concurrent" Java impl is a recent optimization for high-throughput system services. Standard `std::mutex` is likely fast enough for most cases.
