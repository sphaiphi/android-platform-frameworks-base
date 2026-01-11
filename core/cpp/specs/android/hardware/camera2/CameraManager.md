# CameraManager - Reverse Engineering Documentation

## Executive Summary
`CameraManager` is a system service that acts as the entry point for interacting with camera devices. It provides methods for discovering available cameras, querying their characteristics, and opening them for use. It also manages system-wide camera events like device connection/disconnection and torch (flashlight) state changes.

## Architecture Overview
- **Service Type**: System-level service retrieved via `Context.getSystemService(Context.CAMERA_SERVICE)`.
- **Backend Interaction**: Communicates with the `ICameraService` (native camera service) via AIDL.
- **Client Side**: Uses `CameraManagerGlobal` (a singleton) to manage callbacks and service connections.
- **Concurrency**: Operations are typically asynchronous, using `Executor` and `Handler` for callbacks.

## Detailed Functionality

### Camera Discovery
**Purpose**: To list all camera sensors available on the device.
**Algorithm**:
1. Application calls `getCameraIdList()`.
2. `CameraManager` queries the native camera service for the list of available camera IDs.
3. Native service returns IDs for all physical and logical cameras.
4. Returns a `String[]` of IDs.

### Querying Characteristics
**Purpose**: To get static information about a camera without opening it.
**Algorithm**:
1. Application calls `getCameraCharacteristics(cameraId)`.
2. `CameraManager` requests the static metadata for that ID from the native service.
3. The native service returns a `CameraMetadataNative` object.
4. `CameraManager` wraps it in a `CameraCharacteristics` object and returns it.

### Opening a Camera
**Purpose**: To establish a session with a camera device.
**Algorithm**:
1. Application calls `openCamera(cameraId, callback, handler)`.
2. `CameraManager` initiates the connection via `ICameraService`.
3. The native service verifies permissions and device availability.
4. If successful, a `CameraDeviceImpl` is created and returned to the application via the `onOpened` callback.

## Data Model

### CameraManagerGlobal
- **Singleton**: Manages the connection to the native `ICameraService`.
- **Callback Map**: Tracks registered `AvailabilityCallback` and `TorchCallback` listeners.
- **Device State**: Maintains a local cache of camera availability to provide fast responses to simple queries.

## API Reference

### Public Methods
- `String[] getCameraIdList()`: Get IDs of all available cameras.
- `CameraCharacteristics getCameraCharacteristics(String cameraId)`: Get static properties.
- `void openCamera(String cameraId, CameraDevice.StateCallback callback, Handler handler)`: Open a connection to a camera.
- `void registerAvailabilityCallback(AvailabilityCallback callback, Handler handler)`: Listen for camera connection changes.
- `void setTorchMode(String cameraId, boolean enabled)`: Turn the camera flash on/off as a flashlight.

## Java-to-C++ Translation Guide

### Service Management
- **Java**: `Context.getSystemService`.
- **C++**: Use `android::IServiceManager` to find the `media.camera` service and obtain an `android::ICameraService` binder.

### Callback Handling
- **Java**: Uses `Handler` or `Executor` for thread-safe callbacks.
- **C++**: Use a dedicated `android::Looper` or a thread pool for executing callbacks from the binder threads to avoid blocking the IPC.

### Error Handling
- **Java**: Throws `CameraAccessException` for various failures.
- **C++**: Return `android::status_t` and use `android::binder::Status` for IPC errors. Map these to a C++ exception or an `std::expected` error type.

## Test Cases & Validation
1. **Camera Enumeration**: Verify that `getCameraIdList` returns at least one camera on a device with hardware.
2. **Availability Monitoring**: Register an `AvailabilityCallback` and simulate a camera disconnect/connect (e.g., via a virtual device) to ensure the callback fires.
3. **Torch Control**: Toggle torch mode and verify the physical flash state (if possible) or the `TorchCallback`.

## Implementation Risks
- **Permission Management**: Handling the `android.permission.CAMERA` permission correctly at the system level is complex.
- **Multi-Client Arbitration**: The camera service manages which app gets access to the camera based on priority; the manager must handle `CAMERA_IN_USE` errors gracefully.
- **Logical vs. Physical**: Managing the relationship between logical camera IDs and their underlying physical IDs requires careful mapping.
