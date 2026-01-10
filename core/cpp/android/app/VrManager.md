# VrManager - Reverse Engineering Documentation

## Executive Summary
`VrManager` provides access to system-level Virtual Reality (VR) capabilities. It allows applications to query and control the VR mode state, manage persistent VR mode (for VR viewer integration), configure 2D virtual display properties, and bind to compositor services. It acts as a client wrapper for the `IVrManager` AIDL interface.

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.VR_SERVICE`.
- **Backend Communication**: Uses `IVrManager` for IPC with the system server.
- **Callback Framework**: Uses `CallbackEntry` to wrap user-provided `VrStateCallback` objects, ensuring they are executed on the requested `Executor`.

## Detailed Functionality

### Mode Management
- `isVrModeEnabled()`: Returns true if the system is currently in VR mode.
- `setPersistentVrModeEnabled(boolean enabled)`: Forces the device into VR mode, even if the foreground activity doesn't request it. This is typically used by VR shell apps or viewers.

### State Callbacks
**Purpose**: Notifying apps of mode transitions.
**Logic**: 
- `registerVrStateCallback`: Adds a listener for both standard VR mode and persistent VR mode changes.
- Uses `IVrStateCallbacks` and `IPersistentVrStateCallbacks` Binder stubs to receive updates from the system server.

### 2D Virtual Display
**Mechanism**: `setVr2dDisplayProperties(Vr2dDisplayProperties)` allows configuring the resolution and DPI of the surface where 2D apps are rendered in VR.

### Compositor Binding
**Mechanism**: `setAndBindVrCompositor(ComponentName)` identifies the background service responsible for rendering the VR environment (the "compositor").

## API Reference
- `public boolean isVrModeEnabled()`: Mode query.
- `public void registerVrStateCallback(...)`: Event registration.
- `public void setVr2dDisplayProperties(...)`: Layout config.
- `public int getVr2dDisplayId()`: Returns the ID of the VR virtual display.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use AIDL-generated C++ interface `android::service::vr::IVrManager`.
- **Callback Proxy**: Implement C++ classes for `IVrStateCallbacks` and `IPersistentVrStateCallbacks`.
- **Map Management**: Use `std::map<VrStateCallback*, std::unique_ptr<CallbackEntry>>` to track registered listeners.

## Implementation Risks
- **Permission Enforcement**: Requires `RESTRICTED_VR_ACCESS` or `ACCESS_VR_STATE`. C++ callers must ensure they hold the necessary privileges.
- **Remote Latency**: State queries and callback registrations involve IPC. C++ logic should be mindful of potential blocking on the main thread.
- **Lifecycle Leaks**: Ensure that all registered callbacks are unregistered when the client is destroyed.
