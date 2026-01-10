# CameraExtensionCharacteristics.java - Reverse Engineering Documentation

## Executive Summary
`CameraExtensionCharacteristics` allows clients to query the availability, supported resolutions, and specific capabilities of device-specific camera extensions (e.g., HDR, Night mode, Bokeh). It bridges the gap between the standard Camera2 API and specialized vendor implementations.

## Architecture Overview
- **Type**: Data/Query Class
- **Package**: `android.hardware.camera2`
- **Dependencies**: `android.hardware.camera2.extension.ICameraExtensionsProxyService` (IPC to vendor service).

## Supported Extensions
-   `EXTENSION_AUTOMATIC` (0)
-   `EXTENSION_FACE_RETOUCH` (1)
-   `EXTENSION_BOKEH` (2)
-   `EXTENSION_HDR` (3)
-   `EXTENSION_NIGHT` (4)

## Detailed Functionality

### Vendor Proxy Service
The class uses a global singleton `CameraExtensionManagerGlobal` to bind to a proxy service (`com.android.cameraextensions.CameraExtensionsProxyService`). This service provides the actual implementation of the extensions.
-   Supports a **Fallback Mechanism**: If a vendor implementation is missing, it can use a software-based fallback defined in system config.

### Capability Queries
-   **Supported Sizes**: `getExtensionSupportedSizes` returns resolutions for both repeating (preview) and single-capture requests.
-   **Latency**: `getEstimatedCaptureLatencyRangeMillis` provides an estimate of processing time for multi-frame captures.
-   **Metadata Keys**: `getKeys(extension)` returns which `CameraCharacteristics` keys have extension-specific values (e.g., different zoom ranges in Night mode).
-   **Postview**: `isPostviewAvailable` checks if a low-res placeholder image can be returned before the final high-quality processed image.

## Java-to-C++ Translation Guide

### IPC Strategy
In C++, this requires a Binder client for the `ICameraExtensionsProxyService`.

```cpp
class CameraExtensionCharacteristics {
public:
    std::vector<int32_t> getSupportedExtensions() const;
    std::vector<Size> getExtensionSupportedSizes(int extension, int format) const;
    // ...
private:
    sp<ICameraExtensionsProxyService> mProxyService;
};
```

### Implementation Notes
-   **Service Binding**: The Java implementation uses `Context.bindService`. In C++, this would involve `IServiceManager` or a similar native service discovery mechanism.
-   **Metadata Wrapping**: Many methods return metadata values by wrapping `CameraMetadataNative` returned from the proxy service into `CameraCharacteristics`. C++ should maintain this separation.
