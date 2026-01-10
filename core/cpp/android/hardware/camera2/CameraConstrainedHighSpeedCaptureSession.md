# CameraConstrainedHighSpeedCaptureSession.java - Reverse Engineering Documentation

## Executive Summary
`CameraConstrainedHighSpeedCaptureSession` is a specialized subclass of `CameraCaptureSession` designed for high-speed video recording (>= 120 FPS). It enforces specific constraints on request patterns and hardware capabilities to achieve the performance necessary for high-frame-rate capture.

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Extends**: `CameraCaptureSession`.
- **Constraint**: Only accepts requests created via `createHighSpeedRequestList`.

## Detailed Functionality

### High-Speed Constraints
1.  **Surfaces**: Supports at most 2 output surfaces (typically a preview surface and a recording surface). Both must have the same size and be chosen from `StreamConfigurationMap.getHighSpeedVideoSizes`.
2.  **Request Batching**: To reduce IPC overhead and maintain high frame rates, requests are batched.
3.  **Automatic Overrides**: The camera device overrides several 3A controls to `AUTO` or `FAST` modes (AE, AWB, AF). Manual control is restricted.
4.  **FPS Range**: Requests must use an FPS range supported by `StreamConfigurationMap.getHighSpeedVideoFpsRangesFor`.

### Core Method
-   **`createHighSpeedRequestList(CaptureRequest)`**: Generates a list of requests with interleaved patterns (e.g., ensuring preview is at least 30fps while recording is at the target high rate) that the hardware can consume efficiently.

## Java-to-C++ Translation Guide

### Design Pattern
This is a **Specialized Session** pattern. In C++, this should be a derived class that overrides submission methods to validate the high-speed requirements.

```cpp
class CameraConstrainedHighSpeedCaptureSession : public CameraCaptureSession {
public:
    virtual std::vector<CaptureRequest> createHighSpeedRequestList(
        const CaptureRequest& request) = 0;
};
```

### Implementation Notes
-   **Validation**: The implementation must strictly check that the input `CaptureRequest` contains valid surfaces and FPS ranges before expanding it into a burst list.
-   **Performance**: Minimizing allocations when creating the request list is critical given the high frame rate context.
