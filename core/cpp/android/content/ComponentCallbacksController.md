# ComponentCallbacksController - Reverse Engineering Documentation

## Executive Summary
`ComponentCallbacksController` is a helper class to manage a list of `ComponentCallbacks` objects and dispatch events to them. It is used by `Context` implementations (like `ContextImpl` or `Application`) to handle registry.

## Architecture Overview
- **Pattern:** Observer Pattern (Subject).
- **Thread Safety:** Synchronized access to the listener list.

## Detailed Functionality
- **`registerCallbacks`**: Adds a listener.
- **`unregisterCallbacks`**: Removes a listener.
- **`dispatchConfigurationChanged`**: Iterates and calls `onConfigurationChanged`.
- **`dispatchLowMemory`**: Iterates and calls `onLowMemory`.
- **`dispatchTrimMemory`**: Iterates, checks if listener instanceof `ComponentCallbacks2`, and calls `onTrimMemory`.

## Data Model
- `mComponentCallbacks`: `List<ComponentCallbacks>`.
- `mLock`: `Object` for synchronization.

## API Reference
- `public void registerCallbacks(ComponentCallbacks callbacks)`
- `public void unregisterCallbacks(ComponentCallbacks callbacks)`
- `public void dispatchConfigurationChanged(Configuration newConfig)`

## Java-to-C++ Translation Guide
- **RTTI**: `instanceof ComponentCallbacks2` requires RTTI (`dynamic_cast` in C++) to verify if the callback supports `onTrimMemory`.

## Implementation Risks
- **Concurrency**: Modifications to the list during iteration (though `forAllComponentCallbacks` copies to array to avoid `ConcurrentModificationException`).
