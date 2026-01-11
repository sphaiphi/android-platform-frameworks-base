# SurfaceControlActivePictureListener - Reverse Engineering Documentation

## Executive Summary
`SurfaceControlActivePictureListener` is a system-level observer that allows privileged components to monitor which compositor layers are using picture processing. it provides a callback that reports an array of `SurfaceControlActivePicture` records whenever the set of active processing layers changes.

## Architecture Overview
*   **Role**: Global compositor processing monitor.
*   **IPC**: Registers a native listener with the `WindowManagerService` (WMS) or `SurfaceFlinger`.
*   **Security**: Guarded by the `OBSERVE_PICTURE_PROFILES` permission.

## Detailed Functionality
*   **`onActivePicturesChanged()`**: The primary callback providing the list of active layers.
*   **`startListening()`** / **`stopListening()`**: Manages the native binder lifecycle.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::gui::IActivePictureListener` (AIDL).
*   **Lifecycle**: Uses `NativeAllocationRegistry` to ensure native cleanup.

## Implementation Risks
*   **Overhead**: This listener tracks global compositor state; high-frequency changes in visible layers can lead to a storm of callbacks.
