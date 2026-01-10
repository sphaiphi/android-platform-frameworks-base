# Filter - Reverse Engineering Documentation

## Executive Summary
`Filter` is an abstract base class for asynchronous data filtering. It is used by `Filterable` adapters (like `ArrayAdapter`, `CursorAdapter`) to perform search queries on a background thread without blocking the UI.

## Architecture Overview
*   **Type**: Abstract Class.
*   **Role**: Async Worker.
*   **Key Methods**:
    *   `performFiltering(CharSequence)`: Background worker method.
    *   `publishResults(...)`: UI thread callback.

## Detailed Functionality
*   **Threading**:
    *   Maintains a `HandlerThread` ("Filter") to process requests sequentially.
    *   Uses a `RequestHandler` to run `performFiltering`.
    *   Uses a `ResultsHandler` to post results back to the UI thread.
*   **Debouncing**: Supports `Delayer` to throttle keystrokes.
*   **Cancellation**: Cancels previous pending requests if a new one arrives.

## Java-to-C++ Translation Guide
*   **Threading**: Use `std::thread`, `std::future`, or a task queue.
*   **Cancellation**: Need a mechanism to invalidate tokens or flags for stale requests.

## Implementation Risks
*   **Concurrency**: Ensure thread safety when accessing data structures in `performFiltering` vs reading them in `publishResults`.
