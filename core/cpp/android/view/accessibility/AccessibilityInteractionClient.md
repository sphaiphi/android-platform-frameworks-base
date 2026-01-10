# AccessibilityInteractionClient - Reverse Engineering Documentation

## Executive Summary
A Singleton (per thread) client that handles the complexity of querying the view hierarchy. It manages IPC with the system service and the ViewRoot (via `IAccessibilityInteractionConnection`). It handles the "same-thread" optimization where if the client and the provider are in the same thread, IPC is skipped.

## Architecture
*   **Singleton**: `getInstanceForThread(long threadId)`.
*   **Connection Cache**: Stores `IAccessibilityServiceConnection` mappings.
*   **Callbacks**: Implements `IAccessibilityInteractionConnectionCallback` to receive async results from ViewRoots.

## Key Algorithms
*   **`findAccessibilityNodeInfoByAccessibilityId`**:
    1.  Checks cache (`AccessibilityCache`).
    2.  If miss, initiates IPC to `IAccessibilityServiceConnection`.
    3.  Waits for result using `waitForResultTimedLocked`.
    4.  Caches the result.
*   **Same-Thread Optimization**: If the request is targeted at the same thread, `ViewRootImpl` passes the message directly to `setSameThreadMessage`, and `waitForResultTimedLocked` executes it immediately instead of waiting on a condition variable.
*   **Prefetching**: Logic to prefetch ancestors/descendants/siblings to populate the cache and reduce IPC chatter.

## Java-to-C++ Translation Guide
*   **Synchronization**: Uses `Object.wait()`/`notifyAll()`. Maps to `std::condition_variable`.
*   **IPC**: Heavy Binder usage.
*   **Thread Local Storage**: Manages instances per thread ID.
