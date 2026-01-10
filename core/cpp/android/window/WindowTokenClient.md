# WindowTokenClient - Reverse Engineering Documentation

## Executive Summary
`WindowTokenClient` is the fundamental binder object that lives in the client process and receives `Configuration` and lifecycle updates from the WindowManager hierarchy in the system server. It acts as the "anchor" for `WindowContext` and `WindowProviderService`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` extends `Binder`
*   **Role**: Client-side Configuration Receiver.

## Detailed Functionality

### Configuration Updates (`onConfigurationChanged`)
**Logic**:
1.  Receives `newConfig` and `newDisplayId`.
2.  Checks `shouldUpdateResources` via `ConfigurationHelper`.
3.  **Synchronization**: Locks on internal `mConfiguration`.
4.  **Action**:
    *   Updates the `Resources` via `ResourcesManager.updateResourcesForActivity`.
    *   Calls `dispatchConfigurationChanged` on the associated context.
    *   Clears text layout caches if needed.

### Lifecycle
*   `onWindowTokenRemoved()`: Called when the window token is destroyed. Destroys the associated context.

## Java-to-C++ Translation Guide

### Binder Stub
*   Corresponds to an AIDL interface (likely `IWindowTokenClient` implicitly, though it extends `Binder` directly in Java).
*   In C++, implement `BnWindowTokenClient`.

### Dependencies
*   `ResourcesManager`: Java-only. C++ implementation would need a mechanism to reload native assets or notify native UI components.

## Implementation Risks
*   **Thread Safety**: Must handle callbacks on arbitrary binder threads while potentially updating UI state (which often requires the main thread). Java uses a `Handler` to post to the main loop.
