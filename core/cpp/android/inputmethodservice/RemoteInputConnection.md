# RemoteInputConnection - Reverse Engineering Documentation

## Executive Summary
`RemoteInputConnection` implements the `InputConnection` interface in the IME process. It delegates calls to the application process via `IRemoteInputConnection` (wrapped by `IRemoteInputConnectionInvoker`). It handles the "client" side of the connection from the IME's perspective.

## Architecture Overview
*   **Implements**: `InputConnection`.
*   **Dependencies**: `IRemoteInputConnectionInvoker`, `InputMethodServiceInternal`.

## Detailed Functionality

### Method Forwarding
*   Most methods (e.g., `commitText`, `deleteSurroundingText`) simply forward to `mInvoker`.
*   **`notifyUserActionIfNecessary`**: Called after modifying calls (commit, delete, sendKeyEvent) to notify the system that the user is interacting (updating rotation/timeout timers).

### Batch Edit
*   `beginBatchEdit` / `endBatchEdit`: Forwarded to remote.

### State Checking
*   Checks `mCancellationGroup.isCanceled()` before making calls to avoid calling into a dead/unbound connection.

## Data Model
*   `mInvoker`: The binder proxy wrapper.
*   `mImsInternal`: Helper to notify service.

## Java-to-C++ Translation Guide
*   **Proxy Pattern**: Straightforward proxy.
*   **Concurrency**: `CompletableFuture` handling in Invoker needs C++ equivalent.

## Implementation Risks
*   **Blocking**: Some IC calls are blocking. `RemoteInputConnection` waits for them (with timeout). This must be handled carefully to avoid freezing the IME.
