# IInputMethodWrapper - Reverse Engineering Documentation

## Executive Summary
`IInputMethodWrapper` adapts the `IInputMethod` Binder interface to the `InputMethod` interface. Similar to the session wrapper, it marshals calls from Binder threads to the main thread. It acts as the entry point for the system (`InputMethodManagerService`) to control the IME service.

## Architecture Overview
*   **Inheritance**: `IInputMethod.Stub` -> `IInputMethodWrapper`.
*   **Implements**: `HandlerCaller.Callback`.
*   **Context**: Holds a `WeakReference` to `InputMethodServiceInternal` and `InputMethod`.

## Detailed Functionality

### Message Dispatch (`executeMessage`)
*   Handles commands: `DO_INITIALIZE_INTERNAL`, `DO_BIND_INPUT`, `DO_START_INPUT`, `DO_SHOW_SOFT_INPUT`, `DO_HIDE_SOFT_INPUT`, etc.
*   **Validation**: Checks `isValid` (references not null, service not destroyed) before execution.
*   **Tracing**: Integrates with `ImeTracker` for latency logging.

### Input Binding Lifecycle
*   **`bindInput`**: Creates a `RemoteInputConnection` wrapping the `IRemoteInputConnection` provided by the client. Initializes `mCancellationGroup`.
*   **`unbindInput`**: Cancels the `mCancellationGroup` to invalidate pending async operations in `RemoteInputConnection`.
*   **`startInput`**: Sets up the input connection and dispatches `dispatchStartInput` to the IME.

### Session Creation
*   **`createSession`**: Wraps the callback in `InputMethodSessionCallbackWrapper` to handle the asynchronous session creation and return the `IInputMethodSessionWrapper` stub.

### Stylus Handwriting
*   Forwards handwriting start/finish, init ink window, etc.

## Data Model
*   `mTarget`: WeakRef to `InputMethodServiceInternal`.
*   `mCancellationGroup`: Manages cancellation of async input connection calls when unbinding.

## Java-to-C++ Translation Guide
*   **Binder**: Corresponds to `BnInputMethod`.
*   **Weak References**: Critical to prevent leaks; the wrapper should not keep the service alive if it's being destroyed.
*   **Async Handling**: The `CancellationGroup` pattern is important for cleaning up pending futures when the input context is lost.

## Implementation Risks
*   **Protocol**: Order of `bindInput` -> `startInput` -> `unbindInput` is guaranteed by the system but must be strictly handled.
*   **Stats Token**: `ImeTracker.Token` needs to be passed correctly for system metrics.
