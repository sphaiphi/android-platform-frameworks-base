# CameraSharedCaptureSession.java - Reverse Engineering Documentation

## Executive Summary
`CameraSharedCaptureSession` enables shared camera access where multiple clients can open the same camera concurrently. This is used in multi-client scenarios (e.g., two apps or a system component and an app).

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Extends**: `CameraCaptureSession`.
- **Visibility**: `@SystemApi`.

## Detailed Functionality

### Client Roles
-   **Primary Client**: Can create/modify capture requests and control 3A parameters.
-   **Secondary Client**: Cannot modify parameters. Can only start/stop a default stream using `startStreaming`.

### Restrictions
-   Shared sessions have a predefined configuration (`CameraCharacteristics.SHARED_SESSION_CONFIGURATION`).
-   Bursts, reprocessing, and offline switching are **not supported** in shared mode.

## Java-to-C++ Translation Guide
This requires a sophisticated arbitrator in the native camera service to handle client priorities (based on OOM scores and process state).

```cpp
class CameraSharedCaptureSession : public CameraCaptureSession {
public:
    virtual int startStreaming(const std::vector<Surface*>& surfaces, ...) = 0;
};
```
