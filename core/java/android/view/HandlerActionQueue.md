# HandlerActionQueue - Reverse Engineering Documentation

## Executive Summary
`HandlerActionQueue` is an internal utility used by `View` to enqueue pending work (Runnables) when the view is not yet attached to a window (and thus has no `Handler`). Once the view is attached, these actions are flushed to the view's newly associated `Handler`.

## Architecture Overview
*   **Role**: Temporary work buffer for unattached views.
*   **Lifecycle**:
    1.  `post()` / `postDelayed()`: Adds actions to an internal array.
    2.  `executeActions(Handler)`: Called when the view attaches; it schedules all buffered tasks on the provided handler.

## Detailed Functionality
*   **Array Management**: Uses `GrowingArrayUtils` to dynamically resize the storage for pending actions.
*   **Matching**: Supports `removeCallbacks()` by comparing `Runnable` equality.

## Java-to-C++ Translation Guide
*   **Storage**: In C++, use a `std::vector` of a struct containing a function pointer (or `std::function`) and a delay timestamp.
*   **Threading**: This class is NOT thread-safe in Java; the C++ implementation should likely be guarded by a mutex if accessed across threads.

## Implementation Risks
*   **Execution Order**: Ensure that the sequence of posted actions is preserved during the flush to the handler.
*   **Memory**: Since this is a temporary buffer, failing to call `executeActions` or `removeCallbacks` on a view that is never attached can lead to small memory leaks.
