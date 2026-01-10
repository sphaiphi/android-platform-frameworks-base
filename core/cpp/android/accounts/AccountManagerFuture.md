
# AccountManagerFuture - Reverse Engineering Documentation

## Executive Summary
`AccountManagerFuture<V>` is an interface that represents the future result of an asynchronous operation initiated via the `AccountManager`. It is a specialized version of the standard `java.util.concurrent.Future` pattern, tailored for the specific exceptions and blocking behavior of the accounts framework. It allows a caller to cancel an operation, check its status, and block to retrieve the final result.

## Architecture Overview
*   **Future Design Pattern**: It follows the "Future" design pattern, providing a placeholder for a result that will be available later. This is the core mechanism that allows `AccountManager` methods to be asynchronous, returning immediately while work happens in the background.
*   **Specialized Exceptions**: The key difference from a standard `java.util.concurrent.Future` is in its `getResult()` methods. Instead of throwing a generic `ExecutionException`, it is specified to throw one of three checked exceptions: `OperationCanceledException`, `AuthenticatorException`, or `IOException`. This provides callers with more specific, actionable information about why an authentication operation failed.
*   **Interface**: It is an interface, not a concrete class. The actual implementation is a private inner class within `AccountManager` (e.g., `Future2Task`) which bridges the Binder IPC response mechanism to this Future interface.

## Detailed Functionality

### `cancel(boolean mayInterruptIfRunning)`
*   **Purpose**: To attempt to cancel the asynchronous operation.
*   **Behavior**: This method signals the `AccountManagerService` and the associated authenticator that the client is no longer interested in the result. Its success is not guaranteed; if the operation has already completed, cancellation will fail. The `mayInterruptIfRunning` parameter is a hint about whether the underlying work should be interrupted.
*   **C++ Implementation Guidance**: In a `std::future`-based implementation, cancellation is not natively supported in the same way. It is often handled via shared state (e.g., a `std::atomic_bool`) that the asynchronous task can periodically check. Alternatively, a more advanced future/promise library (like Boost.Thread or a custom one) that supports cancellation would be needed to replicate this behavior.

### `isCancelled()`
*   **Purpose**: To check if the operation was successfully cancelled before it completed normally.
*   **C++ Implementation Guidance**: If using a shared cancellation flag, this would check the state of that flag.

### `isDone()`
*   **Purpose**: To check if the operation has completed, either by succeeding, failing, or being cancelled. This method never blocks.
*   **C++ Implementation Guidance**: This is equivalent to checking the `valid()` status of a `std::future` or using the `wait_for` method with a zero timeout.

### `getResult()` and `getResult(long timeout, TimeUnit unit)`
*   **Purpose**: To retrieve the result of the operation, blocking until it is available (or until the timeout expires). This is the "synchronous" part of the pattern.
*   **Behavior**:
    *   If called on the main UI thread, it is expected to throw an `IllegalStateException` (this is enforced by the concrete implementation in `AccountManager`).
    *   If the operation was successful, it returns the result of type `V` (e.g., a `Bundle`).
    *   If the operation was cancelled, it throws `OperationCanceledException`.
    *   If the authenticator or network failed, it throws `AuthenticatorException` or `IOException`.
*   **C++ Implementation Guidance**: This directly maps to `std::future::get()`. The C++ asynchronous task would need to wrap its exceptions in a way that they can be re-thrown by `get()`. This can be done by using `std::promise::set_exception(std::make_exception_ptr(...))`. The C++ `get()` method would then re-throw the stored exception. The three specific Java exceptions would need to be translated into a hierarchy of C++ exception classes.

## Java-to-C++ Translation Guide
*   **`std::future<V>`**: The standard C++ library's `std::future<V>` is the most direct equivalent. It provides `get()`, `wait_for()`, and `valid()`.
*   **Custom Future Implementation**: To fully replicate the functionality, especially the specific checked exceptions and cancellation, a custom C++ Future/Promise implementation might be necessary. This would involve a shared state object managed by a `Promise` and a `Future` class. The `Promise`, held by the asynchronous task, would store either the result value or an `std::exception_ptr`. The `Future`, held by the client, would access this shared state to retrieve the result or re-throw the exception.
*   **Exception Translation**: C++ exception classes corresponding to `OperationCanceledException`, `AuthenticatorException`, and `IOException` would need to be created.

    ```cpp
    // Example C++ Exception Hierarchy
    class AccountsException : public std::runtime_error { ... };
    class OperationCanceledException : public AccountsException { ... };
    class AuthenticatorException : public AccountsException { ... };
    class IOException : public AccountsException { ... };
    ```
    The asynchronous task would catch its internal errors and call `promise.set_exception` with the appropriate C++ exception type.

## Implementation Risks
*   **Blocking on UI Thread**: A critical aspect of the Java implementation is preventing `getResult()` from being called on the main thread. A C++ implementation must have a robust way to detect this and fail loudly, as blocking the UI thread is a major source of application hangs and "Application Not Responding" (ANR) errors.
*   **Cancellation**: As mentioned, `std::future` does not have built-in cancellation. Simply letting a `future` go out of scope does not cancel the underlying task. A C++ implementation must explicitly decide on and implement a cancellation strategy if that feature is required.

## Questions for C++ Team
*   Is the full `cancel()` functionality required, or is a simpler `std::future` model (without cancellation) sufficient?
*   What is the C++ strategy for detecting and preventing blocking calls on the main UI thread?
*   Should we create a custom C++ exception hierarchy to match the Java `AccountsException` types?
