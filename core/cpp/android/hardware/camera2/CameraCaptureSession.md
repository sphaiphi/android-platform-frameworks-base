# CameraCaptureSession.java - Reverse Engineering Documentation

## Executive Summary
`CameraCaptureSession` represents a configured set of surfaces for a `CameraDevice` to capture images or reprocess existing ones. It is the primary interface for submitting capture requests (bursts, repeating, or single-shot) once the camera hardware has been configured.

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Implements**: `AutoCloseable`.
- **Role**: Manages the pipeline state between the application and the camera service.

## Detailed Functionality

### Lifecycle and Configuration
-   **Creation**: Created via `CameraDevice.createCaptureSession`. The process is asynchronous and involves significant hardware setup (pipeline configuration, buffer allocation).
-   **State Callbacks**: Notifies the app via `CameraCaptureSession.StateCallback` (`onConfigured`, `onConfigureFailed`, `onReady`, `onActive`, `onClosed`).
-   **Closing**: Closing a session stops repeating requests but finishes in-progress ones.

### Buffer Management
-   **`prepare(Surface)`**: Pre-allocates buffers for an output surface to minimize latency during the first capture.
-   **`tearDown(Surface)`**: Frees allocated buffers to save memory.
-   **`finalizeOutputConfigurations`**: Finalizes deferred surfaces (e.g., from `SurfaceView` before layout is complete).

### Capture Operations
-   **`capture(...)`**: Submits a one-time request.
-   **`captureBurst(...)`**: Submits a list of requests to be processed in sequence without interleaving.
-   **`setRepeatingRequest(...)`**: Endless capture (e.g., for preview).
-   **`stopRepeating()`**: Cancels repeating requests.
-   **`abortCaptures()`**: Discards all pending and in-progress work as fast as possible.

### Reprocessing
-   **`isReprocessable()`**: Indicates if this session can take input from a surface (e.g., for Zero Shutter Lag).
-   **`getInputSurface()`**: Returns the surface where the app provides input for reprocessing.

### Offline Processing
-   **`switchToOffline(...)`**: Migrates pending requests to an `CameraOfflineSession`, allowing the camera to be closed or switched while processing continues.

## API Reference

### Inner Classes
-   **`StateCallback`**: Listens for session-level events.
-   **`CaptureCallback`**: Listens for individual request progress (`onCaptureStarted`, `onCaptureProgressed`, `onCaptureCompleted`, `onCaptureFailed`).

## Java-to-C++ Translation Guide

### Abstract Interface
In C++, this maps to a pure virtual interface.

```cpp
namespace android::hardware::camera2 {

class ICameraCaptureSession {
public:
    virtual ~ICameraCaptureSession() = default;
    
    virtual int capture(const CaptureRequest& request, 
                        ICaptureCallback* listener, 
                        IHandler* handler) = 0;
    virtual int setRepeatingRequest(const CaptureRequest& request, 
                                    ICaptureCallback* listener, 
                                    IHandler* handler) = 0;
    virtual void stopRepeating() = 0;
    virtual void abortCaptures() = 0;
    // ...
};

}
```

### Synchronization
The Java implementation uses `Handler` and `Executor` for asynchronous callbacks. The C++ implementation should use a similar mechanism (e.g., an event loop or `ALooper`).

### Implementation Risks
-   **State Management**: Complex internal state transitions (Configuring -> Active -> Ready -> Closed).
-   **Buffer Lifetimes**: Ensuring surfaces are valid during the entire session lifetime.
-   **Thread Safety**: Methods must be thread-safe as they are often called from UI or background processing threads.
