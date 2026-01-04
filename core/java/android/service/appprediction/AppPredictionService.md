# AppPredictionService - Reverse Engineering Documentation

## Executive Summary
`AppPredictionService` is an abstract base class for services that predict app usage and shortcuts. It manages prediction sessions, handles event notifications (app launches, location updates), and provides sorted lists of app targets to clients (like the launcher).

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IPredictionService.Stub` (anonymous inner class) to expose functionality to the system server.
*   **Session Management**: Maintains a mapping of `AppPredictionSessionId` to lists of callbacks (`mSessionCallbacks`).
*   **Threading**: Uses a `Handler` on the main looper to marshal IPC calls to the main thread.

## Detailed Functionality

### Core IPC Wrapper (`mInterface`)
The `IPredictionService.Stub` implementation handles incoming AIDL calls and posts them to the `mHandler` to be executed on the main thread.
*   **Methods Handled**:
    *   `onCreatePredictionSession`
    *   `notifyAppTargetEvent`
    *   `notifyLaunchLocationShown`
    *   `sortAppTargets`
    *   `registerPredictionUpdates`
    *   `unregisterPredictionUpdates`
    *   `requestPredictionUpdate`
    *   `onDestroyPredictionSession`
    *   `requestServiceFeatures`

### Session Lifecycle
1.  **Creation**: `onCreatePredictionSession` is called. The service creates an entry in `mSessionCallbacks`.
2.  **Updates**: Clients register callbacks via `registerPredictionUpdates`.
3.  **Destruction**: `onDestroyPredictionSession` is called. The service removes the session and cleans up callbacks.

### Prediction Logic
*   **Events**: `onAppTargetEvent` and `onLaunchLocationShown` notify the service of user actions.
*   **Sorting**: `onSortAppTargets` requests the service to rank a provided list of `AppTarget` objects.
*   **Updates**: `onRequestPredictionUpdate` allows clients to pull new predictions. `updatePredictions` allows the service to push new predictions to registered callbacks.

### Callback Management (`CallbackWrapper`)
*   Wraps `IPredictionCallback`.
*   Handles `linkToDeath` to automatically unregister callbacks if the client process dies.
*   Converts `List<AppTarget>` to `ParceledListSlice` for IPC transport.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.appprediction.AppPredictionService"`

### Abstract Methods (To be implemented by subclasses)
*   `void onAppTargetEvent(AppPredictionSessionId, AppTargetEvent)`
*   `void onLaunchLocationShown(AppPredictionSessionId, String, List<AppTargetId>)`
*   `void onSortAppTargets(AppPredictionSessionId, List<AppTarget>, CancellationSignal, Consumer<List<AppTarget>>)`
*   `void onRequestPredictionUpdate(AppPredictionSessionId)`

### Lifecycle Methods
*   `void onCreatePredictionSession(AppPredictionContext, AppPredictionSessionId)`
*   `void onDestroyPredictionSession(AppPredictionSessionId)`
*   `void onStartPredictionUpdates()`
*   `void onStopPredictionUpdates()`

### Protected/Final Methods
*   `void updatePredictions(AppPredictionSessionId, List<AppTarget>)`: Sends updates to clients.

## Java-to-C++ Translation Guide

### Threading Model
*   **Java**: Uses `Handler` and `Looper.getMainLooper()` to ensure service methods run on the main thread.
*   **C++**: Ensure a similar message loop or task queue is used if the service implementation is single-threaded. AIDL calls come in on binder threads.

### IPC / Binder
*   **Java**: `IPredictionService.Stub`.
*   **C++**: `BnPredictionService` (generated from AIDL).
*   **Death Recipients**: `linkToDeath` is crucial. In C++, use `IBinder::linkToDeath`.

### Data Structures
*   `AppPredictionSessionId`, `AppTarget`, `AppTargetEvent`, `AppPredictionContext` need C++ equivalents.
*   `ParceledListSlice` is a specific Android Java container for large lists over Binder. In C++, standard `std::vector` or `Parcel` read/write might be used depending on the generated AIDL.

### Containers
*   `ArrayMap<AppPredictionSessionId, ArrayList<CallbackWrapper>>`: Map of session IDs to lists of callbacks. C++: `std::map` or `std::unordered_map`.

## Implementation Risks
*   **Memory Leaks**: Callbacks must be unregistered properly on binder death or session destruction.
*   **Concurrency**: Access to `mSessionCallbacks` must be synchronized if the C++ implementation is multi-threaded (though the Java one serializes to the main thread).
*   **Binder Limits**: Large lists of targets in `updatePredictions` could hit binder transaction limits. `ParceledListSlice` helps handles this in Java; C++ needs equivalent logic (e.g., chunking or using shared memory if very large).
