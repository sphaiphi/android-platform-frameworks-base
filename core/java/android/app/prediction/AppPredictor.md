# AppPredictor - Reverse Engineering Documentation

## Executive Summary
`AppPredictor` is the client-side controller for an app prediction session. It maintains a persistent session with the system service (`IPredictionManager`), sends events (clicks, impressions), and registers callbacks to receive prediction updates.

## Architecture Overview
*   **Pattern**: Client-Service (Proxy).
*   **Protocol**: AIDL (`IPredictionManager`).
*   **State**: Manages a local `AppPredictionSessionId` and a map of registered callbacks.
*   **Lifecycle**: Explicit `destroy()` method to clean up server-side resources.

## Detailed Functionality

### Initialization (`constructor`)
**Algorithm**:
1.  Obtains `IPredictionManager` binder from `ServiceManager` (service name: "app_prediction").
2.  Generates a unique `AppPredictionSessionId`.
    *   Format: `PackageName + ":" + UUID.randomUUID()`
    *   Includes UserID.
3.  Calls `mPredictionManager.createPredictionSession(context, sessionId, token)`.
4.  Opens `CloseGuard`.

### Event Reporting
*   `notifyAppTargetEvent(AppTargetEvent)`: Forwards event to service.
*   `notifyLaunchLocationShown(String, List<AppTargetId>)`: Forwards impression data (Launch location + list of shown IDs) to service.
*   **Check**: Both methods throw `IllegalStateException` if `destroy()` has been called.

### Prediction Updates
*   `registerPredictionUpdates(Executor, Callback)`:
    *   Wraps the user-provided `Callback` in a `CallbackWrapper` (extends `IPredictionCallback.Stub`).
    *   The wrapper handles thread dispatch using the `Executor`.
    *   Registers with service via `registerPredictionUpdates`.
    *   Stores wrapper in `mRegisteredCallbacks` map.
*   `unregisterPredictionUpdates(Callback)`:
    *   Removes from map.
    *   Unregisters from service.

### On-Demand Requests
*   `requestPredictionUpdate()`: Asks service to push a new update via registered callbacks.
*   `sortTargets(List<AppTarget>, Executor, Consumer)`: Asks service to sort a provided list of targets. Uses a one-off `CallbackWrapper`.
*   `requestServiceFeatures(...)`: Asks service for feature bundle.

### Lifecycle (`destroy`)
**Algorithm**:
1.  Sets `mIsClosed` atomic flag.
2.  Closes `CloseGuard`.
3.  Calls `mPredictionManager.onDestroyPredictionSession`.
4.  Clears registered callbacks.

## Data Model

| Java Field | Type | Description |
| :--- | :--- | :--- |
| `mPredictionManager` | `IPredictionManager` | Binder proxy to system service. |
| `mSessionId` | `AppPredictionSessionId` | Unique session ID. |
| `mRegisteredCallbacks` | `ArrayMap<Callback, CallbackWrapper>` | Map of user callbacks to binder stubs. |
| `mIsClosed` | `AtomicBoolean` | Destroyed state flag. |

## API Reference
*   See `IPredictionManager` AIDL for the underlying IPC contract.

## Java-to-C++ Translation Guide

### Binder Interfaces
*   Need generated C++ code for `IPredictionManager` and `IPredictionCallback`.

### Callback Management
*   C++ equivalent of `CallbackWrapper` must inherit from `BnPredictionCallback`.
*   Need a mechanism to dispatch callbacks to a specific thread (Looper/Handler) if mirroring the Executor pattern.

### UUID Generation
*   Use `boost::uuids` or platform specific UUID generation for the session ID.

### Error Handling
*   Java rethrows `RemoteException` as `RuntimeException`.
*   C++ should return `android::binder::Status` or `android::status_t`.

## Implementation Risks
*   **Concurrency**: Access to `mRegisteredCallbacks` is synchronized. C++ must use `std::mutex`.
*   **Memory Management**: `CallbackWrapper` in Java is kept alive by the map. In C++, ensure the `sp<IPredictionCallback>` is kept alive as long as it's registered.
*   **Service Death**: The Java code doesn't explicitly handle service death (linkToDeath), likely relying on the calling app crashing or handling the RemoteException. C++ might want robust death handling.

## Questions for C++ Team
*   Is there a standard `Executor` equivalent for callback dispatch in the C++ framework layer? (Likely `looper`).
