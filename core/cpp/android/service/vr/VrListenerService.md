# VrListenerService - Reverse Engineering Documentation

## Executive Summary
`VrListenerService` is an abstract base class for services that are bound by the system while the device is running in Virtual Reality (VR) mode. It allows a dedicated VR management application to be notified of lifecycle changes in VR activities and transitions between 3D VR content and 2D compatibility mode.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IVrListener.Stub`.
*   **Binding Lifecycle**:
    *   The system binds to this service when an Activity that has called `setVrModeEnabled(true, componentName)` gains focus.
    *   The service is unbound when the system leaves VR mode.
*   **Permission**: Requires `android.permission.BIND_VR_LISTENER_SERVICE`.
*   **User Control**: The service must be explicitly enabled by the user in the "VR helper services" settings.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IVrListener` binder interface.

### Core Callback
*   **`onCurrentVrActivityChanged(ComponentName component, boolean running2dInVr, int pid)`**:
    *   **Goal**: Notify the listener when the foreground VR application changes.
    *   **component**: The name of the new VR activity.
    *   **running2dInVr**: True if the system is displaying a standard 2D app inside a VR environment (compatibility mode).
    *   **pid**: The process ID of the new activity.

### Static Utilities
*   **`isVrModePackageEnabled(Context, ComponentName)`**: Checks if the specified listener is currently authorized in the system settings.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.vr.VrListenerService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IVrListener.Stub`.
*   **C++**: `BnVrListener`.

### Process Management
*   The `pid` parameter is provided to allow the listener to perform process-level optimizations (e.g., setting CPU/GPU affinity or priority for the VR app).

## Implementation Risks
*   **Transition Latency**: VR transitions are performance-critical. The listener must not perform heavy operations on the binder thread during `onCurrentVrActivityChanged`.
*   **Stability**: If the VR listener crashes, the system's ability to manage VR state (like thermal limits or display modes) might be compromised.
*   **State Consistency**: The listener should maintain its own internal state of whether the system is currently in VR mode based on bind/unbind events.
