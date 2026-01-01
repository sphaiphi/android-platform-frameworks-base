# CameraExtensionSession.java - Reverse Engineering Documentation

## Executive Summary
`CameraExtensionSession` is a specialized capture session for using device-specific camera extensions. It simplifies access to complex vendor algorithms (multi-frame fusion, post-processing) while abstracting the underlying pipeline complexity.

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Implements**: `AutoCloseable`.
- **Role**: Executes requests through the extension pipeline.

## Detailed Functionality

### Extension Capture Callbacks
Provides a specialized `ExtensionCaptureCallback` with extra hooks:
-   `onCaptureProcessStarted`: Called when post-processing actually begins.
-   `onCaptureProcessProgressed`: Provides a 0-100 estimate of processing progress (for slow extensions).
-   `onCaptureResultAvailable`: Returns a subset of metadata supported by the extension.

### Operational Modes
-   **Repeating Request**: Primarily for preview. The extension is allowed to override almost all capture parameters to optimize for the effect.
-   **Capture**: Single high-quality output. Usually limited to one or two output surfaces (Capture + Postview).

### Latency Tracking
-   **`getRealtimeStillCaptureLatency()`**: Returns `StillCaptureLatency` which splits time into capture (sensor) and processing (algorithm) durations.

## Java-to-C++ Translation Guide

### Abstract Interface
```cpp
class ICameraExtensionSession {
public:
    virtual int capture(const CaptureRequest& request, 
                        IExtensionCaptureCallback* listener, 
                        IExecutor* executor) = 0;
    virtual int setRepeatingRequest(const CaptureRequest& request, 
                                    IExtensionCaptureCallback* listener, 
                                    IExecutor* executor) = 0;
};
```

### Key Differences from Standard Session
-   **Parameter Overrides**: C++ implementation must account for the fact that the vendor extension might ignore most keys set in `CaptureRequest`.
-   **Limited Surfaces**: Enforce the "max two surfaces" rule during submission.
