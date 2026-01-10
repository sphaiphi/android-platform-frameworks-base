# ConcurrentMessageQueue - Reverse Engineering Documentation

## Executive Summary
`ConcurrentMessageQueue` is a modern, high-performance implementation of the Android MessageQueue designed for high-throughput system services. Unlike `LegacyMessageQueue`, which uses a global lock, `ConcurrentMessageQueue` employs non-blocking algorithms (Treiber stack, ConcurrentSkipListSet) and fine-grained locking to allow multiple threads to enqueue messages simultaneously without contention.

## Architecture Overview
-   **Core Pattern**: Hybrid lock-free stack + Priority Queue.
-   **Data Structures**:
    -   **Treiber Stack (`mStateValue`)**: A lock-free LIFO stack used as the primary ingestion point for new messages (`enqueueMessage`). This allows very fast, non-blocking insertion.
    -   **Priority Queues (`mPriorityQueue`, `mAsyncPriorityQueue`)**: `ConcurrentSkipListSet`s used to sort messages by timestamp (`when`) and sequence (`mInsertSeq`). Messages are moved here from the stack during the `next()` loop.
-   **State Machine**:
    -   `STACK_NODE_ACTIVE`: The consumer thread (`next()`) is actively processing messages or draining the stack.
    -   `STACK_NODE_PARKED`: The consumer is sleeping indefinitely.
    -   `STACK_NODE_TIMEDPARK`: The consumer is sleeping until a specific deadline.

## Detailed Functionality

### Message Ingestion (`enqueueMessage`)
-   **Lock-Free Insertion**: Uses `VarHandle.compareAndSet` on `sState` (the stack top) to push a new `MessageNode`.
-   **Wakeup Logic**:
    -   If the consumer is `ACTIVE`, no wakeup is needed (it will see the new node when draining).
    -   If the consumer is `PARKED`, `nativeWake` is called.
    -   If `TIMEDPARK`, wakeup is conditional on the new message's timestamp being earlier than the current wake deadline.

### Message Consumption (`next`)
-   **Draining Phase**:
    -   Acquires `mDrainingLock`.
    -   Swaps the stack state to `ACTIVE` using CAS.
    -   **Reverses** the LIFO stack order while moving nodes into the `ConcurrentSkipListSet` (Priority Queue). This restores the correct time ordering.
-   **Selection Phase**:
    -   Peeks at `mPriorityQueue` and `mAsyncPriorityQueue`.
    -   Handles **Sync Barriers**: If the head of the synchronous queue is a barrier (null target), it strictly looks for the next *asynchronous* message.
    -   **Comparison**: Uses `pickEarliestNode` to decide between the sync and async queues based on timestamp and sequence.
-   **Delivery**:
    -   If a message is ready (`now >= when`), it returns it.
    -   Otherwise, it calculates the next sleep timeout and transitions the state to `TIMEDPARK` (or `PARKED` if empty).

### Concurrency Control
-   **VarHandles**: Used extensively (`sState`, `sNextInsertSeq`, `sCounts`, `sQuitting`) for atomic field updates.
-   **Fine-grained Locks**:
    -   `mDrainingLock`: Coordinates the stack drain phase to ensure only one thread acts as the "drainer" at a time (though effectively `next()` is single-threaded per Looper).
    -   `mIdleHandlersLock`: Protects idle handler list.
    -   `mFileDescriptorRecordsLock`: Protects FD listeners.

## Data Model
-   **`StackNode`**: Base class for stack items. Can be a `MessageNode` or a `StateNode`.
-   **`MessageNode`**: Wrapper around `Message` containing linkage pointers and sequence numbers.
-   **`StateNode`**: Sentinel nodes (`Active`, `Parked`, `TimedPark`) marking the bottom of the stack and current loop state.

## API Reference
-   **`enqueueMessage`**: High-performance, thread-safe insertion.
-   **`next`**: Retrieving the next message, handling waits and barriers.
-   **`postSyncBarrier` / `removeSyncBarrier`**: Standard barrier API logic adapted for the concurrent structures.

## Java-to-C++ Translation Guide
-   **Complexity Warning**: This class relies heavily on Java's `ConcurrentSkipListSet` and `VarHandle`. Porting this to C++ requires robust lock-free data structures.
-   **Equivalent Structures**:
    -   Stack: `std::atomic<Node*>` implementing a Treiber stack.
    -   Priority Queue: `std::priority_queue` (guarded by a lock) or a concurrent skiplist implementation if available (e.g., `folly::ConcurrentSkipList`). Given the "Single Consumer" nature of `next()`, a standard priority queue might suffice *after* draining the shared stack.
-   **Memory Ordering**: Java `volatile` and `VarHandle` imply specific memory barriers. C++ `std::atomic` with `std::memory_order_acq_rel` is the direct equivalent.

## Implementation Risks
-   **ABA Problem**: The Treiber stack is susceptible to ABA. Java's GC handles this naturally. In C++, you **must** use hazard pointers, epoch reclamation, or versioned pointers (if 128-bit CAS is available) to avoid use-after-free corruption in the lock-free stack.
-   **Livelock**: Heavy contention on `enqueueMessage` CAS loops could starve threads. Backoff strategies might be needed in C++.
