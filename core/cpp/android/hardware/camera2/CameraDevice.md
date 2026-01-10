# CameraDevice.java - Reverse Engineering Documentation

## Executive Summary
`CameraDevice` represents a single camera connected to an Android device. It is the core object used to create capture requests and sessions. It exposes hardware-level capabilities and manages the high-level lifecycle of the camera connection.

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Implements**: `AutoCloseable`.
- **Role**: Acts as a factory for `CaptureRequest.Builder` and `CameraCaptureSession`.

## Detailed Functionality

### Request Templates
Provides predefined templates for common use cases:
-   `TEMPLATE_PREVIEW` (1): Prioritizes frame rate.
-   `TEMPLATE_STILL_CAPTURE` (2): Prioritizes image quality.
-   `TEMPLATE_RECORD` (3): Stable frame rate for video.
-   `TEMPLATE_VIDEO_SNAPSHOT` (4): Quality snapshot during recording.
-   `TEMPLATE_ZERO_SHUTTER_LAG` (5): Best quality without preview stall.
-   `TEMPLATE_MANUAL` (6): Direct control of all parameters.

### Session Management
-   **`createCaptureSession(SessionConfiguration)`**: The modern way to start camera streaming. Aggregates output surfaces, callbacks, and parameters.
-   **`createExtensionSession`**: For device-specific augmented modes (HDR, Night, Bokeh).
-   **`isSessionConfigurationSupported`**: Runtime check if a specific configuration is valid without actually opening the camera hardware.

### Audio and Privacy
-   **`setCameraAudioRestriction`**: Mutes vibrations/sounds from other apps to prevent audio interference during recording.

### Inner Classes
-   **`StateCallback`**: Listens for hardware-level events (`onOpened`, `onDisconnected`, `onError`).
-   **`CameraDeviceSetup`**: A limited representation allowing queries and session checks without the full latency cost of creating a full `CameraDevice`.

## API Reference

| Method | Return Type | Description |
| :--- | :--- | :--- |
| `getId()` | `String` | Returns the unique camera ID. |
| `createCaptureRequest(int template)` | `CaptureRequest.Builder` | Factory for requests. |
| `createCaptureSession(SessionConfig)`| `void` | Begins session configuration. |
| `close()` | `void` | Closes the camera. |

## Java-to-C++ Translation Guide

### Core Interface
```cpp
namespace android::hardware::camera2 {

class ICameraDevice {
public:
    virtual ~ICameraDevice() = default;
    
    virtual std::string getId() const = 0;
    virtual std::unique_ptr<CaptureRequest::Builder> createCaptureRequest(int templateId) = 0;
    virtual void createCaptureSession(const SessionConfiguration& config) = 0;
    virtual void close() = 0;
};

}
```

### Hardware Levels
C++ implementation must respect the `INFO_SUPPORTED_HARDWARE_LEVEL` (LEGACY, LIMITED, FULL, LEVEL3, EXTERNAL) when implementing template defaults and validating session configurations.

### Key Considerations
-   **Shared Mode**: `openSharedCamera` allows multiple clients. This implies a complex arbitration logic in the backend service.
-   **Physical vs Logical**: Handling logical multi-cameras requires mapping physical camera IDs to specific outputs within a single session.
