# RemoteCallbackList - Reverse Engineering Documentation

## Executive Summary
`RemoteCallbackList` manages a list of registered `IInterface` (Binder) callbacks. It handles thread-safe iteration, broadcasting updates, and automatically cleaning up callbacks when the remote process dies (`linkToDeath`).

## Architecture Overview
-   **Pattern**: Observer Registry.
-   **Storage**: `ArrayMap<IBinder, Interface>`.
-   **Death Handling**: Each registered callback is wrapped in an `Interface` object that implements `IBinder.DeathRecipient`.

## Detailed Functionality
-   **`register(E callback, Object cookie)`**: Adds callback, links to death.
-   **`beginBroadcast()`**: Locks the list, creates a snapshot (`mActiveBroadcast`) for iteration. Returns count.
-   **`getBroadcastItem(index)`**: Returns item from snapshot.
-   **`finishBroadcast()`**: Unlocks/clears snapshot.
-   **`broadcast(Consumer<E>)`**: Helper for lambda-based iteration.

## Java-to-C++ Translation Guide
-   **Equivalent**: `RemoteCallbackList` logic exists in some C++ system services but isn't a standard NDK class.
-   **Implementation**: Use `std::vector` or `std::map` of `sp<IInterface>`.
-   **Death**: Implement `startOneWayBinderTransaction` or similar mechanism to handle death. `Binder::linkToDeath` is essential.
-   **Locking**: Crucial to prevent deadlocks during broadcast (don't hold the lock while calling the remote interface). The `beginBroadcast` snapshot pattern is specifically designed to avoid this.

## Implementation Risks
-   **Deadlocks**: Calling remote methods while holding the list lock is a classic bug. The snapshot approach prevents this.
