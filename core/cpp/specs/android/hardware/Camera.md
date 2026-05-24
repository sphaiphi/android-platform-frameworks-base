# Camera - Reverse Engineering Documentation

## Executive Summary
The `Camera` class is the legacy API for managing camera hardware on Android devices. It allows applications to set capture settings, start/stop previews, take pictures, and retrieve frames for video encoding. It acts as a client to the system-wide Camera service.

**Note**: This class is deprecated in favor of `android.hardware.camera2`.

## Architecture Overview
The `Camera` class follows a client-server architecture. The Java class is a wrapper around native C++ logic (`mNativeContext`) that communicates with the Camera service via Binder. It uses an internal `EventHandler` (extending `Handler`) to dispatch messages from the native layer to the Java callbacks on the thread that opened the camera.

## Detailed Functionality

### Camera Lifecycle
1. **Open**: `open(int)` or `open()` connects to the camera service.
2. **Setup**: `setPreviewDisplay(SurfaceHolder)` or `setPreviewTexture(SurfaceTexture)` is mandatory for preview.
3. **Parameters**: `getParameters()` and `setParameters(Parameters)` configure the hardware.
4. **Preview**: `startPreview()` starts the stream.
5. **Action**: `takePicture(...)` captures a still image. `autoFocus(...)` triggers focus.
6. **Release**: `release()` must be called to free hardware for other apps.

### `takePicture(ShutterCallback, PictureCallback, PictureCallback, PictureCallback)`
**Purpose**: Triggers an asynchronous image capture.
**Algorithm**:
1. Sets up callbacks for shutter, raw, postview, and jpeg.
2. Calls `native_takePicture(msgType)` where `msgType` is a bitmask of required callbacks.
3. Stops preview automatically.
**Java-Specific Notes**: Callbacks are delivered via the `EventHandler` using `Looper`.
**C++ Implementation Guidance**: Implement as a non-blocking call that triggers the HAL. Use a messaging system to return data to the caller.

### `autoFocus(AutoFocusCallback)`
**Purpose**: Starts camera auto-focus.
**Algorithm**: Registers the callback and calls `native_autoFocus()`.
**Java-Specific Notes**: If hardware doesn't support autofocus, it immediately returns success via callback.

### `release()`
**Purpose**: Disconnects from the camera service and cleans up.
**Algorithm**: Calls `native_release()`, resets state, and stops watching AppOps for shutter sound.

## Data Model
- **CameraInfo**:
    - `facing`: `CAMERA_FACING_BACK` (0) or `CAMERA_FACING_FRONT` (1).
    - `orientation`: Degrees (0, 90, 180, 270).
    - `canDisableShutterSound`: boolean.
- **Face**:
    - `rect`: `Rect` of detected face.
    - `score`: Confidence (1-100).
    - `id`, `leftEye`, `rightEye`, `mouth`: Optional tracking info.

## API Reference (Partial)
- `public static Camera open(int cameraId)`
- `public final void release()`
- `public final void startPreview()`
- `public final void stopPreview()`
- `public final void takePicture(ShutterCallback shutter, PictureCallback raw, PictureCallback postview, PictureCallback jpeg)`
- `public final void setDisplayOrientation(int degrees)`
- `public final void setParameters(Parameters params)`

## Java-to-C++ Translation Guide
- **Native State**: `mNativeContext` (long) should map to a pointer to a native `Camera` object or a wrapper struct in C++.
- **Callbacks**: Use `std::function` or specialized listener interfaces.
- **Threading**: Native callbacks from the camera service must be dispatched to the correct event loop (e.g., using a message queue or executor).
- **AppOps**: C++ implementation needs to interact with the native AppOps service if shutter sound control is required.

## Test Cases & Validation
- Open and release camera multiple times to check for resource leaks.
- Verify preview displays correctly on a `Surface`.
- Verify picture callbacks return non-null byte arrays of expected formats.
- Test error handling when opening a camera already in use.

## Implementation Risks
- **Thread Safety**: The class is explicitly not thread-safe. C++ implementation must enforce or document this.
- **Deprecated Status**: Compatibility with modern HAL versions (HAL 3.0+) is required even for this legacy API.
- **Resource Management**: Failing to release the camera can lock the hardware for the entire system.
