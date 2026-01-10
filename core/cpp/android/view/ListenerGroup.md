# ListenerGroup - Reverse Engineering Documentation

## Executive Summary
`ListenerGroup` is a non-thread-safe utility class used to manage a collection of listeners. It provides a "replay" mechanism where the last reported value is automatically sent to any new listener upon registration.

## Architecture Overview
*   **Role**: Listener lifecycle manager.
*   **Wrapper**: Wraps each consumer in a `ListenerWrapper` which bundles it with an `Executor`.

## Detailed Functionality
*   **`accept(T value)`**: Updates the "last known value" and dispatches it to all current listeners.
*   **`addListener()`**: Adds a new consumer and immediately triggers a callback with the current state.
*   **Deduplication**: Prevents adding the same consumer multiple times.

## Java-to-C++ Translation Guide
*   **Storage**: In C++, use a `std::vector<std::unique_ptr<ListenerWrapper<T>>>`.
*   **Threading**: While the Java version is not thread-safe, a C++ implementation in a multi-threaded UI toolkit should likely use a `std::mutex` for the listener list.

## Implementation Risks
*   **Ownership**: The group must ensure that the `Executor` (or equivalent callback queue) outlives the dispatch cycle.
