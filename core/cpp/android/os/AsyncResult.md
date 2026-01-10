# AsyncResult - Reverse Engineering Documentation

## Executive Summary
`AsyncResult` is a generic container used for asynchronous callback results, typically in the Message-based callback pattern used by `Handler`. It holds the result data, any exception that occurred, and a user-provided context object.

## Architecture Overview
-   **Pattern**: Callback Result / Tuple.
-   **Usage**: Widely used in Telephony and System services to return data via `Message.obj`.

## Data Model
-   `userObj` (Object): User-defined cookie passed in the original request.
-   `result` (Object): The operation result (success).
-   `exception` (Throwable): The error (failure).

## API Reference
-   `forMessage(Message m, Object r, Throwable ex)`: Static factory that populates `m.obj` with the `AsyncResult`.

## Java-to-C++ Translation Guide
-   **Equivalent**: A struct or class template `AsyncResult<T>` holding `T result`, `status_t error`, and `void* cookie`.
-   **Memory**: Java handles object lifecycles; C++ would need to manage ownership of the `result` and `userObj`.
