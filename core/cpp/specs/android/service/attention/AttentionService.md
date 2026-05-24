# AttentionService - Reverse Engineering Documentation

## Executive Summary
`AttentionService` is an abstract base class for services that provide user attention estimation (e.g., checking if the user is looking at the screen) and proximity detection. It is used by the system (via `AttentionManagerService`) for features like "Screen Attention" (keeping screen on while looking).

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IAttentionService.Stub` (anonymous inner class).
*   **Permissions**: Requires `android.permission.BIND_ATTENTION_SERVICE`.
*   **Configuration**: The implementation is defined in `config_AttentionComponent`.

## Detailed Functionality

### Core Operations
1.  **Check Attention**: Single-shot request to determine if the user is paying attention.
2.  **Cancel Check**: Cancels a pending attention check.
3.  **Proximity Updates**: Continuous stream of proximity distance updates.

### `onBind(Intent intent)`
**Purpose**: Binds the service if the intent matches `SERVICE_INTERFACE`.
**Returns**: `IAttentionService.Stub`.

### `IAttentionService.Stub` Implementation
*   **`checkAttention`**: Wraps the AIDL callback in `AttentionCallback` and calls `onCheckAttention`.
*   **`cancelAttentionCheck`**: Wraps the callback and calls `onCancelAttentionCheck`.
*   **`onStartProximityUpdates`**: Wraps the callback in `ProximityUpdateCallback` and calls `onStartProximityUpdates`.
*   **`onStopProximityUpdates`**: Calls `onStopProximityUpdates`.

### Abstract/Overridable Methods
*   `onCheckAttention(AttentionCallback callback)`: Abstract. Must be implemented to perform the check.
*   `onCancelAttentionCheck(AttentionCallback callback)`: Abstract. Must cancel the specific check.
*   `onStartProximityUpdates(ProximityUpdateCallback callback)`: Optional. Starts proximity sensing.
*   `onStopProximityUpdates()`: Optional. Stops proximity sensing.

## Data Model

### Constants / Status Codes
*   **Success**: `ATTENTION_SUCCESS_ABSENT` (0), `ATTENTION_SUCCESS_PRESENT` (1).
*   **Failure**: `ATTENTION_FAILURE_UNKNOWN`, `ATTENTION_FAILURE_CANCELLED`, `ATTENTION_FAILURE_PREEMPTED`, `ATTENTION_FAILURE_TIMED_OUT`, `ATTENTION_FAILURE_CAMERA_PERMISSION_ABSENT`.
*   **Proximity**: `PROXIMITY_UNKNOWN` (-1).

### Inner Classes
*   **`AttentionCallback`**: Wrapper around `IAttentionCallback`.
    *   `onSuccess(int result, long timestamp)`
    *   `onFailure(int error)`
*   **`ProximityUpdateCallback`**: Wrapper around `IProximityUpdateCallback` (holds a `WeakReference`).
    *   `onProximityUpdate(double distance)`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IAttentionService.Stub`.
*   **C++**: `BnAttentionService`.

### Callback Management
*   **Java**: Wrappers handle `RemoteException`.
*   **C++**: Implementation must handle binder transactions to the callback interface.

### Resource Management
*   Attention checks often involve camera or specific sensors.
*   **C++**: Ensure camera resources are released when `onCancelAttentionCheck` or `onStopProximityUpdates` is called, or when the binder dies (linkToDeath).

## Implementation Risks
*   **Privacy**: Access to camera/sensors for attention checking is sensitive.
*   **Performance**: Attention checks should be fast and power-efficient.
*   **Concurrency**: `onCheckAttention` might be called while another check is pending (though usually serialized by the system service, the service implementation should be robust).
