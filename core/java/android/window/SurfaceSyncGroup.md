# SurfaceSyncGroup - Reverse Engineering Documentation

## Executive Summary
`SurfaceSyncGroup` allows synchronization of surface updates across different windows, views, and even processes. It aggregates `SurfaceControl.Transaction`s from multiple sources and applies them atomically once all participants are ready.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class`
*   **Role**: Synchronization primitive.
*   **Key Interfaces**: `ISurfaceSyncGroup`, `ITransactionReadyCallback`.

## Detailed Functionality

### Core Logic
*   **Sync Ready**: Participants call `markSyncReady()`.
*   **Adding Participants**: `add(SurfaceView)`, `add(AttachedSurfaceControl)`, `add(SurfacePackage)`.
*   **Merging**: If a SyncGroup is added to another, they merge state. The child calls `setTransactionCallbackFromParent`.
*   **Remote Sync**: If adding a participant from another process, it calls `WindowManagerGlobal.addToSurfaceSyncGroup`. This delegates the coordination to the WindowManagerService (WMS) to prevent untrusted transaction injection.

### Transaction Collection
*   Uses an internal `Transaction mTransaction`.
*   When a child is ready, `onTransactionReady(Transaction t)` is called. `t` is merged into `mTransaction`.
*   When all children are ready and `markSyncReady` is called, the final transaction is either applied (root) or sent to the parent (child).

### Timeout
*   Implements a timeout (default 1s) using `HandlerThread` ("SurfaceSyncGroupTimer") to prevent indefinite blocking if a participant crashes or hangs.

## Java-to-C++ Translation Guide

### Binder Interfaces
*   `ISurfaceSyncGroup`, `ITransactionReadyCallback`.
*   Use `BnSurfaceSyncGroup`, `BnTransactionReadyCallback`.

### Synchronization
*   The logic relies heavily on `synchronized(mLock)`. Use `std::mutex`.
*   `Handler`/`Looper` logic for timeout can be replaced by `looper` or `std::thread` with sleep/condition variable.

## Implementation Risks
*   **Deadlocks**: Merging groups can create complex dependency graphs. The `parentSyncGroupMerge` flag handles some edge cases (reversing merge order).
*   **Cross-Process Security**: WMS is used as a trusted intermediary. The C++ implementation in the system server must enforce this security boundary.
