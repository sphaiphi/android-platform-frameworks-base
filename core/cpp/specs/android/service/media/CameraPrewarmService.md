# CameraPrewarmService - Reverse Engineering Documentation

## Executive Summary
`CameraPrewarmService` is an abstract service that allows camera applications to perform early initialization (pre-warming) when a camera launch gesture is detected (e.g., double-tapping the power button). This reduces the startup latency of the camera activity.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Uses a `Messenger` to receive a signal from the system when the camera intent is officially fired.
*   **Lifecycle**:
    *   `onBind`: Triggers `onPrewarm()`.
    *   `onUnbind`: Triggers `onCooldown(boolean)`.
*   **Configuration**: The service is identified via metadata in the manifest (see `MediaStore.META_DATA_STILL_IMAGE_CAMERA_PREWARM_SERVICE`).

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Starts the pre-warm phase.
**Mechanism**:
1.  Verifies the action is `ACTION_PREWARM`.
2.  Calls the abstract `onPrewarm()` method.
3.  Returns a binder from a `Messenger` that listens for `MSG_CAMERA_FIRED`.

### `onUnbind(Intent intent)`
**Purpose**: Ends the pre-warm phase and triggers cleanup.
**Mechanism**:
1.  Calls `onCooldown(mCameraIntentFired)`.
2.  `mCameraIntentFired` is true if the system sent `MSG_CAMERA_FIRED` while bound.

### Abstract Methods
*   **`onPrewarm()`**: The implementation should start heavy camera initialization (e.g., opening camera hardware, warming up the ISP).
*   **`onCooldown(boolean cameraIntentFired)`**: The implementation should cleanup resources. If `cameraIntentFired` is false, it means the user didn't actually open the camera, and hardware resources should be released immediately.

## API Reference

### Constants
*   `ACTION_PREWARM`: `"android.service.media.CameraPrewarmService.ACTION_PREWARM"`
*   `MSG_CAMERA_FIRED`: 1

## Java-to-C++ Translation Guide

### IPC
*   **Java**: Uses `Messenger`.
*   **C++**: Can be implemented using a simple AIDL interface with a single `onCameraFired()` method, or by manually handling `IMessenger` if following the exact Java pattern.

### Resource Management
*   The pre-warm phase typically involves acquiring high-power hardware resources. It is critical that `onCooldown` releases these if the camera activity doesn't take over.

## Implementation Risks
*   **Power Consumption**: Holding camera hardware open in the background consumes significant battery.
*   **Contention**: If multiple camera apps try to pre-warm, they may conflict for hardware access.
