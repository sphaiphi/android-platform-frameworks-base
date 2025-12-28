# SafeOneTimeExecuteAppFunctionCallback - Reverse Engineering Documentation

## Executive Summary
A thread-safe, one-time-use wrapper for `IExecuteAppFunctionCallback`. It ensures only one result (success or error) is reported and suppresses subsequent calls.

## Architecture Overview
-   **Role**: Callback wrapper / Safety guard.
-   **Concurrency**: Uses `AtomicBoolean` / `AtomicLong`.

## Detailed Functionality
-   **Guard**: `mOnResultCalled` (AtomicBoolean) ensures idempotency.
-   **Swallow Exceptions**: Catches `RemoteException` to prevent crashes if the other end dies.
-   **Metrics**: Tracks execution time via `mExecutionStartTimeAfterBindMillis` and `CompletionCallback`.

## Data Model
-   `mCallback`: Underlying Binder interface.
-   `mCompletionCallback`: Optional local completion hook.

## API Reference
-   `onResult`: Calls success.
-   `onError`: Calls error.
-   `disable`: Prevents future calls.

## Java-to-C++ Translation Guide
-   **Atomics**: `std::atomic<bool>`.
-   **One-time logic**: Critical for Binder callbacks.

## Test Cases & Validation
-   **Double Call**: Call success, then error. Verify error is ignored.
-   **Exception**: Verify RemoteException is logged/swallowed.
