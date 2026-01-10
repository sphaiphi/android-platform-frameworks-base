# CallbackToken - Reverse Engineering Documentation

## Executive Summary
`CallbackToken` is a thread-safe, `Parcelable` utility class used to facilitate asynchronous retrieval of `ContextualSearchState`. It encapsulates a one-time-use `IBinder` token that verifies the identity of the caller to the system server. It acts as a bridge between the client (e.g., an Activity handling contextual search) and the `ContextualSearchManagerService`.

## Architecture Overview
- **Pattern**: Token/Handle pattern with Callback.
- **IPC Mechanism**: Uses standard Android Binder IPC (`IContextualSearchManager`, `IContextualSearchCallback`).
- **Relationship**:
    - Wraps a raw `IBinder` (`mToken`).
    - Uses `IContextualSearchCallback.Stub` (`CallbackWrapper`) to receive results from the system server.
    - Interact with `IContextualSearchManager` (System Service) to initiate the state retrieval.

## Detailed Functionality

### `getContextualSearchState`
**Purpose**: Requests the `ContextualSearchState` from the system service associated with this token.
**Algorithm**:
1.  **State Check**: Synchronously checks `mTokenUsed` flag. If true, invokes `onError` on the callback immediately.
2.  **Mark Used**: Sets `mTokenUsed` to true (atomic/synchronized operation).
3.  **Service Resolution**: Obtains `IContextualSearchManager` via `ServiceManager.getService("contextual_search")`.
4.  **Callback Creation**: Instantiates `CallbackWrapper` (Binder Stub) wrapping the user-provided `Executor` and `OutcomeReceiver`.
5.  **IPC Call**: Invokes `service.getContextualSearchState(mToken, wrapper)`.
6.  **Error Handling**: Catches `RemoteException`. If occurred, rethrows as `RuntimeException` (via `rethrowFromSystemServer`).

**Java-Specific Notes**:
-   **Synchronization**: Uses a generic `Object mLock` for intrinsic locking to ensure `mTokenUsed` is thread-safe.
-   **Anonymous Inner Classes**: The `CallbackWrapper` handles the translation from Binder thread pool context to the user-provided `Executor`.
-   **Binder Identity**: Uses `Binder.withCleanCallingIdentity` in the callback wrapper to ensure the client code runs with its own identity, not the system's.

**C++ Implementation Guidance**:
-   The C++ implementation will essentially be a client-side wrapper around a `sp<IBinder>`.
-   The "single-use" logic must be enforced locally.
-   The Callback mechanism needs to implement the `BnContextualSearchCallback` (native stub) to receive the result.

## Data Model

### `CallbackToken`
| Field | Type | Description |
|-------|------|-------------|
| `mToken` | `IBinder` | The unique identity token. Generated as `new Binder()` on creation. |
| `mTokenUsed` | `boolean` | Tracks if `getContextualSearchState` has been called. Guarded by `mLock`. |

### `CallbackWrapper` (Inner Class)
| Field | Type | Description |
|-------|------|-------------|
| `mCallback` | `OutcomeReceiver<...>` | The user-facing callback. |
| `mExecutor` | `Executor` | The thread execution context for the callback. |

## API Reference

### `void getContextualSearchState(Executor executor, OutcomeReceiver callback)`
-   **Preconditions**: `mTokenUsed` must be false.
-   **Postconditions**: `mTokenUsed` becomes true. Service is invoked.
-   **Thread Safety**: Safe to call from any thread. Callback is invoked on the provided Executor.

### `IBinder getToken()`
-   **Visibility**: Test API / System API (hidden).
-   **Returns**: The underlying `IBinder`.

## Java-to-C++ Translation Guide

| Java Concept | C++ Equivalent | Notes |
|--------------|----------------|-------|
| `Parcelable` | `Parcelable` (Native) | Implement `writeToParcel` and `readFromParcel`. |
| `IBinder` | `sp<IBinder>` | Strong pointer to binder interface. |
| `synchronized(mLock)` | `std::mutex` + `std::lock_guard` | Standard mutex locking. |
| `ServiceManager.getService` | `defaultServiceManager()->getService` | Standard native service retrieval. |
| `OutcomeReceiver` | `std::function` or specific Callback interface | Native equivalent of a success/error callback. |
| `Executor` | `Looper` / `Handler` or `std::thread` | Native async execution model. |

## Implementation Risks
-   **Binder Lifetime**: Ensure the `mToken` binder is kept alive as long as the server needs it.
-   **Callback Reentrancy**: The Java code prevents calling `getContextualSearchState` twice, but the callback wrapper implementation implies the server *could* technically call `onResult` multiple times if not for the "one-time" contract. The Java doc notes "callback could be invoked multiple times" (e.g. split screen), but the `mTokenUsed` check prevents the *request* from happening twice.
-   **Context**: The code uses `ServiceManager.getService(Context.CONTEXTUAL_SEARCH_SERVICE)`. In C++, use the service name string "contextual_search".

## Questions for C++ Team
-   Does the native layer need to support the `OutcomeReceiver` pattern, or will a simple listener interface suffice?
-   Is strict single-use enforcement required in the native layer if the Java layer already handles it? (Likely yes for parity).
