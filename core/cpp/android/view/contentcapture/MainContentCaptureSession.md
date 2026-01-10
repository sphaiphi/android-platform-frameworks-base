# MainContentCaptureSession - Reverse Engineering Documentation

## Executive Summary
The primary implementation of `ContentCaptureSession` attached to an Activity context. It manages the connection to the system service, the direct connection to the service app (optimization), and the event buffer.

## Architecture
*   **Connections**:
    *   `mSystemServerInterface`: `IContentCaptureManager` (Binder).
    *   `mDirectServiceInterface`: `IContentCaptureDirectManager` (Binder to Service App).
*   **Buffering**: `mEvents` (ArrayList) and `mEventProcessQueue` (ConcurrentLinkedQueue).
*   **Threading**: `mContentCaptureHandler` (Background) vs `mUiHandler`. Events are enqueued on UI thread/binder thread and processed on background thread.

## Key Algorithms
*   **`sendEvent`**:
    *   Checks state/flags.
    *   Adds to `mEvents` buffer.
    *   Merging logic for TEXT_CHANGED and VIEW_DISAPPEARED events to reduce chatter.
    *   Flushing logic (`scheduleFlush`) based on timeout or buffer size.
*   **`flush`**: Sends the buffered events via `mDirectServiceInterface.sendEvents`.
*   **`start`**: Calls system server to initiate session. Receives `IContentCaptureDirectManager` via `mSessionStateReceiver`.

## Java-to-C++ Translation Guide
*   **Concurrency**: Critical. Uses `Handler`, `AtomicBoolean`, `ConcurrentLinkedQueue`. C++ equivalent needs thread-safe queue and task runner.
*   **Batching**: Logic for merging text events is important for performance.
