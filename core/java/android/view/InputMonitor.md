# InputMonitor - Reverse Engineering Documentation

## Executive Summary
`InputMonitor` allows privileged applications to monitor streams of `InputEvent`s without being the designated target window for those events. It is primarily used for system-level gesture detection or monitoring focus changes.

## Architecture Overview
*   **Role**: Passive input listener handle.
*   **Key Fields**:
    *   `mInputChannel`: The pipe used to receive events.
    *   `mHost`: A proxy to `IInputMonitorHost` for control.
    *   `mSurface`: The `SurfaceControl` associated with the monitor.

## Detailed Functionality

### 1. Consumption Control
*   **`pilferPointers()`**: (Deprecated) Allows the monitor to "steal" the current touch gesture, preventing it from reaching the underlying windows.

### 2. Lifecycle
*   **`dispose()`**: Explicitly releases the `InputChannel` and `SurfaceControl` handles.

## Java-to-C++ Translation Guide
*   **Representation**: In C++, this is a data carrier for a set of Binder proxies.
*   **Parceling**: Serialization must match the `DataClass` generated logic.

## Implementation Risks
*   **Resource Leak**: Each `InputMonitor` consumes an input channel and a surface. Failing to `dispose()` will leak file descriptors and compositor layers.
*   **Deprecation**: New code should use `InputManager.monitorGestureInput()`.
