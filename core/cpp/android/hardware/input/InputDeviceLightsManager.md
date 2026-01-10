# InputDeviceLightsManager - Reverse Engineering Documentation

## Executive Summary
`InputDeviceLightsManager` is a specialized implementation of `LightsManager` for controlling lights on a specific input device (e.g., keyboard LEDs, game controller lights). It acts as a client-side proxy to the system's `InputManagerService`.

## Architecture Overview
- **Inheritance**: Extends `android.hardware.lights.LightsManager`.
- **Dependency**: Uses `InputManagerGlobal` singleton to communicate with the service.
- **Scope**: One instance per input device ID.

## Detailed Functionality

### Light Management
- **getLights()**: Fetches list of `Light` objects for the device via `InputManagerGlobal`.
- **getLightState()**: Fetches current state of a specific light.
- **openSession()**: Opens a `LightsSession` for controlling lights. Note: `openSession(int priority)` throws `UnsupportedOperationException`.

### InputDeviceLightsSession
- **Purpose**: Controls lifetime of light modification requests.
- **RAII**: Implements `AutoCloseable` and uses `CloseGuard` to ensure sessions are closed.
- **requestLights()**: Sends light change requests to system server via `InputManagerGlobal.requestLights`.
- **close()**: Closes the session on the server side.

## Data Model
- `mDeviceId`: int (Target Input Device ID)
- `mPackageName`: String (Caller's package name)
- `mGlobal`: `InputManagerGlobal` reference.

## API Reference
- `List<Light> getLights()`
- `LightState getLightState(Light light)`
- `LightsSession openSession()`

## Java-to-C++ Translation Guide
- **Light Object**: Equivalent C++ struct/class for `android.hardware.lights.Light`.
- **Session Management**: Use C++ RAII (destructor) instead of `CloseGuard`/`finalize`.
- **IPC**: Calls need to be routed through the equivalent of `InputManagerGlobal` in C++ (likely direct Binder calls to `IInputManager`).

## Test Cases & Validation
- Open session, change light color, close session. Verification requires mocking `IInputManager`.
- Ensure `close()` is called prevents further requests on that session.

## Implementation Risks
- Thread safety of session closing vs usage.
