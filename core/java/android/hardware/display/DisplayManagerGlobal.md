# DisplayManagerGlobal - Reverse Engineering Documentation

## Executive Summary
`DisplayManagerGlobal` is the singleton process-level bridge to the `IDisplayManager` system service. It handles the heavy lifting of caching display info, managing display listeners (multiplexing multiple app listeners into a single binder callback), and dispatching events.

## Architecture Overview
- **Pattern**: Singleton (`getInstance()`).
- **Communication**: Binder IPC (`IDisplayManager`).
- **Caching**: `PropertyInvalidatedCache` for `DisplayInfo`.
- **Event Dispatch**:
    - Registers one `IDisplayManagerCallback` with the system server.
    - Fans out events to registered `DisplayListenerDelegate`s.

## Detailed Functionality

### DisplayInfo Caching
- Uses `PropertyInvalidatedCache<Integer, DisplayInfo>` keyed by `display_info`.
- This minimizes IPC calls for frequent queries like `getDisplayInfo`.

### Listener Management
- `mDisplayListeners`: List of `DisplayListenerDelegate`.
- **Events Mask**: The class calculates a union of all requested event types from all listeners (`calculateEventsMaskLocked`) and updates the registration with the system service (`registerCallbackWithEventMask`).
- **Virtual Display Callbacks**: Wraps `VirtualDisplay.Callback` into `IVirtualDisplayCallback.Stub` to handle IPC from system server for virtual display state changes (Paused/Resumed/Stopped).

### Native Callbacks
- Supports registering a native choreographer (`registerNativeChoreographerForRefreshRateCallbacks`) to receive refresh rate updates directly via JNI (`nSignalNativeCallbacks`).

### Functionality Delegation
- Most methods are direct proxies to `mDm` (the Binder interface), wrapping `RemoteException` into `RuntimeException`.

## Data Model
- `DisplayListenerDelegate`: Holds the listener, executor, and event mask. Handles event filtering and dispatch.
- `mDisplayInfoCache`: SparseArray cache (distinct from the `PropertyInvalidatedCache`?). *Note: The code shows `mDisplayInfoCache` SparseArray but also `mDisplayCache` PropertyInvalidatedCache. `mDisplayInfoCache` seems to be used for event handling logic or legacy purposes, while `mDisplayCache` is the main read cache.*

## Java-to-C++ Translation Guide
- **Singleton**: Standard C++ singleton.
- **Binder**: `android::sp<IDisplayManager>`.
- **Callback Multiplexing**: Critical for performance. C++ implementation should similarly register one binder callback and dispatch to local listeners to avoid flooding the binder driver.
- **Caching**: Implementing a client-side cache for DisplayInfo in C++ is complex but necessary for performance if high-frequency access is needed.

## Key APIs
- `getDisplayInfo(int)`
- `registerDisplayListener(...)`
- `createVirtualDisplay(...)`
