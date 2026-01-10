# CancellationSignal - Reverse Engineering Documentation

## Executive Summary
`CancellationSignal` provides a mechanism to cancel long-running operations. It creates a standard way to signal cancellation across API boundaries, including across Binder IPC via `ICancellationSignal`.

## Architecture Overview
-   **Pattern**: Cancellation Token.
-   **Components**:
    -   **Signal**: The object held by the client to request cancellation (`cancel()`).
    -   **Listener**: The object implementing the operation, registered via `setOnCancelListener`.
    -   **Transport**: `ICancellationSignal` (AIDL) for cross-process signaling.

## Detailed Functionality
-   **`cancel()`**:
    -   Sets `mIsCanceled`.
    -   Invokes `mOnCancelListener.onCancel()`.
    -   Calls `mRemote.cancel()` if attached.
-   **`createTransport()`**: Creates a native `Transport` object (extends Stub) to pass to a remote client.
-   **`fromTransport()`**: Retrieving the local signal from the transport.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::ICancellationSignal` (Binder).
-   **Logic**: The "transport" pattern is a common Binder idiom.
    -   Server creates `CancellationSignal`.
    -   Server passes `createTransport()` (an `IBinder`) to Client.
    -   Client calls `cancel()` on that binder.
    -   Server receives callback and cancels local work.

## Implementation Risks
-   **Race Conditions**: `cancel()` can happen before `setOnCancelListener`. The class handles this by checking `mIsCanceled` immediately upon registration.
