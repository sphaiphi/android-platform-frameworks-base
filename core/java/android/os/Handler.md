# Handler - Reverse Engineering Documentation

## Executive Summary
`Handler` allows sending and processing `Message` and `Runnable` objects associated with a thread's `MessageQueue`. It binds to a specific `Looper` (thread) and provides the mechanism to dispatch work to that thread.

## Architecture Overview
-   **Pattern**: Command Processor / Dispatcher.
-   **Association**: 1 Handler -> 1 Looper -> 1 MessageQueue -> 1 Thread.
-   **Dispatch**:
    -   **Post**: Enqueues a `Runnable` (wrapped in a `Message`).
    -   **SendMessage**: Enqueues a `Message` with data.
    -   **Handle**: `handleMessage()` (subclass override) or `Callback.handleMessage()` executes on the Looper thread.

## Detailed Functionality
-   **Enqueueing**: All `post` and `send` methods eventually call `enqueueMessage` on the `MessageQueue`.
-   **Dispatching**: `dispatchMessage` is called by `Looper`. Priority:
    1.  `msg.callback` (Runnable posted via `post`).
    2.  `mCallback.handleMessage` (if Handler created with a Callback).
    3.  `handleMessage` (subclass implementation).
-   **Sync Barriers**: Supports `setAsynchronous(true)` to create messages that bypass synchronization barriers (used for high-priority UI events like VSYNC).

## Data Model
-   `mLooper`: The thread's looper.
-   `mQueue`: The queue to write to.
-   `mAsynchronous`: If true, all messages sent by this handler are marked async.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::sp<android::MessageHandler>`.
-   **C++ Looper**: The C++ `Looper` has a `sendMessage(handler, message)` API. The `Handler` in C++ is a callback interface (`onMessageReceived`), not the dispatching logic itself (which is in `Looper`).
-   **Lifecycle**: Java Handlers are often potential memory leaks (non-static inner classes holding `this`). C++ needs `sp<>` and `wp<>` to manage this safely.
