# CameraInjectionSession.java - Reverse Engineering Documentation

## Executive Summary
`CameraInjectionSession` handles the state where an external camera feed is injected into the system to replace an internal camera's feed. This is a privileged operation used for testing or specific virtualization scenarios.

## Architecture Overview
- **Type**: Abstract Class
- **Package**: `android.hardware.camera2`
- **Visibility**: `@hide` (Internal System API).
- **Permission**: `android.Manifest.permission.CAMERA_INJECT_EXTERNAL_CAMERA`.

## Detailed Functionality
-   **Injection Lifecycle**: Managed via `close()`, which stops the injection and returns the system to the internal camera feed.
-   **Callbacks**: `InjectionStatusCallback` notifies the caller of success or fatal service/session errors.

## Java-to-C++ Translation Guide
This is a control interface. The C++ equivalent would be a binder proxy to the internal `CameraService` injection endpoints.

```cpp
class CameraInjectionSession : public virtual RefBase {
public:
    virtual void stop() = 0;
};
```
