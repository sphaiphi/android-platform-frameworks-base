# IRemoteInputConnectionInvoker - Reverse Engineering Documentation

## Executive Summary
`IRemoteInputConnectionInvoker` is a utility class that wraps `IRemoteInputConnection` (the binder interface to the editor) to provide a cleaner API. It handles `AndroidFuture` boilerplate, `RemoteException` catching, and `CancellationSignal` beaming. It makes the remote calls look more like local method calls with Future results.

## Architecture Overview
*   **Pattern**: Facade / Proxy / Invoker.
*   **Role**: Helper for `RemoteInputConnection`.

## Detailed Functionality

### Async Method Invocation
*   Methods like `getTextAfterCursor`, `getSurroundingText`:
    *   Create `AndroidFuture<T>`.
    *   Call raw `mConnection` method passing the future.
    *   Catch `RemoteException` and complete the future exceptionally.
    *   Return the future.

### One-Way Method Invocation
*   Methods like `commitText`, `setSelection`:
    *   Call raw `mConnection` method.
    *   Return `true` on success, `false` on `RemoteException`.

### Result Receivers
*   Uses `OnceResultReceiver` (abstract base) to handle async callbacks for `performHandwritingGesture` and `requestTextBoundsInfo`.
*   Dispatches results to a provided `Executor` and `Consumer`.

### Cancellation Beaming
*   **`beam(CancellationSignal)`**: Uses `CancellationSignalBeamer` to send cancellation signals across the binder interface (tokens).

## Data Model
*   `mConnection`: `IRemoteInputConnection`.
*   `mSessionId`: Session ID.
*   `mBeamer`: Sender for cancellation signals.

## Java-to-C++ Translation Guide
*   **Futures**: Use `std::future` or a custom Future type compatible with Binder async results.
*   **Cancellation**: Requires mapping Android's `CancellationSignal` to C++ equivalent if IPC cancellation is supported.

## Implementation Risks
*   **Deadlocks**: Must ensure futures don't block the main thread if waiting synchronously (though this class returns futures, the consumer `RemoteInputConnection` might wait).
