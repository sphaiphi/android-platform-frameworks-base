# ProxyOnBackInvokedDispatcher - Reverse Engineering Documentation

## Executive Summary
`ProxyOnBackInvokedDispatcher` allows registering `OnBackInvokedCallback`s before the actual `WindowOnBackInvokedDispatcher` is available (e.g., before the ViewRootImpl is attached). It temporarily stores the callbacks and transfers them to the real dispatcher once it's set.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` implements `OnBackInvokedDispatcher`
*   **Role**: Proxy / Deferred Registrar.

## Detailed Functionality

### Storage
*   `mCallbacks`: `List<Pair<OnBackInvokedCallback, Integer>>`. Stores callback + priority.
*   `mActualDispatcher`: The real dispatcher (nullable).

### `registerOnBackInvokedCallback`
1.  Checks validity via `Checker`.
2.  Adds to `mCallbacks`.
3.  If `mActualDispatcher` is set, also registers with it immediately.

### `setActualDispatcher`
1.  If existing dispatcher matches, return.
2.  Unregisters all local callbacks from the *old* dispatcher (if any).
3.  Sets new dispatcher.
4.  Registers all callbacks in `mCallbacks` to the *new* dispatcher.
5.  Clears `mCallbacks`.

## Java-to-C++ Translation Guide

### Proxy Pattern
*   Standard proxy pattern.
*   Requires holding references to `OnBackInvokedCallback` objects (Binders).

### Synchronization
*   Java uses `synchronized(mLock)`. C++ needs `std::mutex`.

## Implementation Risks
*   **Reference Counting**: Ensure callbacks held in the list don't leak or get prematurely destroyed.
