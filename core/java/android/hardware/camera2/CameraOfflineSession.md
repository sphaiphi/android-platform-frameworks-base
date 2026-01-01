# CameraOfflineSession.java - Reverse Engineering Documentation

## Executive Summary
`CameraOfflineSession` is a session created when an active `CameraCaptureSession` is switched to offline mode. It allows the camera hardware to be released or used by another session while long-running captures (e.g., high-quality multi-frame processing) continue in the background.

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Extends**: `CameraCaptureSession`.

## Detailed Functionality
-   **Background Processing**: Once switched, pending requests continue. The app can close the `CameraDevice` and the processing will still complete.
-   **Limited API**: Unlike a regular session, it **cannot** accept new capture requests. Only `close()` is fully supported; other methods throw `UnsupportedOperationException`.
-   **Callbacks**: `CameraOfflineSessionCallback` notifies when the session is `onReady` (transition complete), `onIdle` (all tasks done), or `onError`.

## Java-to-C++ Translation Guide
In C++, this would be a specific implementation of the session interface that returns errors for all submission calls.

```cpp
class CameraOfflineSession : public CameraCaptureSession {
public:
    // submission methods return INVALID_OPERATION
};
```
