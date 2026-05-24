# OutputConfiguration - Reverse Engineering Documentation

## Executive Summary
`OutputConfiguration` describes a camera output destination, which typically wraps one or more `Surface` objects. It allows for advanced configuration of output streams, such as surface sharing, deferred surface initialization, and physical camera mapping in logical multi-camera systems.

## Architecture Overview
- **Core Component**: Wraps a `Surface` (or a placeholder for one).
- **Surface Sharing**: Allows multiple surfaces to share the same camera stream to save memory and bandwidth.
- **Deferred Initialization**: Enables creating a session before the actual `Surface` (e.g., from a `SurfaceView`) is fully initialized.
- **Logical Multi-Camera**: Can be pinned to a specific physical camera ID.

## Detailed Functionality

### Surface Sharing
**Purpose**: To allow multiple consumers (e.g., a preview and a video encoder) to receive data from the same internal camera stream.
**Algorithm**:
1. Call `enableSurfaceSharing()`.
2. Add multiple compatible surfaces via `addSurface()`.
3. The camera HAL produces one buffer which is then distributed to all shared surfaces.

### Deferred Surfaces
**Purpose**: To speed up session creation by not waiting for UI components to be ready.
**Algorithm**:
1. Create `OutputConfiguration` with a `Size` and a class (e.g., `SurfaceHolder.class`).
2. Create the capture session.
3. Once the UI is ready, call `addSurface(actualSurface)`.
4. Call `finalizeOutputConfigurations()` on the session.

### Timestamp Base
**Purpose**: To control the time domain of image timestamps.
**Options**:
- `DEFAULT`: Camera decides based on target (e.g., synced to display for preview).
- `SENSOR`: Matches the raw sensor timestamp source.
- `MONOTONIC`: Matches `SystemClock.uptimeMillis`.
- `REALTIME`: Matches `SystemClock.elapsedRealtime`.

## Data Model

### Members
- `mSurfaces` (`List<Surface>`): Target destinations.
- `mRotation` (`int`): Desired output rotation (0, 90, 180, 270).
- `mSurfaceGroupId` (`int`): ID for sharing memory between different streams.
- `mPhysicalCameraId` (`String`): ID of specific physical sensor.
- `mStreamUseCase` (`long`): Purpose of the stream (Preview, Video, etc.).
- `mTimestampBase` (`int`): Clock domain for timestamps.

## API Reference

### Public Methods
- `void addSurface(Surface surface)`: Add a shared surface.
- `void enableSurfaceSharing()`: Enable the sharing feature.
- `void setPhysicalCameraId(String id)`: Map to physical sensor.
- `void setStreamUseCase(long useCase)`: Optimize pipeline for specific usage.
- `void setTimestampBase(int base)`: Configure clock domain.

## Java-to-C++ Translation Guide

### Surface Management
- **Java**: `List<Surface>`.
- **C++**: `std::vector<sp<IGraphicBufferProducer>>` or `std::vector<ANativeWindow*>`.

### Parceling
- **Java**: Implements `Parcelable`.
- **C++**: Must implement `android::Parcelable` to be passed over Binder to the camera service. The binary layout must match the Java parceling logic exactly.

### Memory Layout
- **Java**: Object with many fields.
- **C++**: A struct-like class. Use `String16` or `std::string` for IDs and `int32_t` for enums and flags.

## Test Cases & Validation
1. **Sharing Compatibility**: Verify that surfaces with different sizes cannot be added to the same sharing configuration unless they meet specific criteria.
2. **Deferred Finalization**: Ensure a session can be created with a deferred surface and that captures only start after `finalizeOutputConfigurations`.
3. **Rotation Mapping**: Verify that requested rotation is correctly applied by the HAL or the consumer.

## Implementation Risks
- **Surface Lifetimes**: Surfaces are heavy objects; ensuring they are not leaked when an `OutputConfiguration` is destroyed is critical.
- **JNI Mapping**: This class is frequently passed across the JNI boundary. The native C++ implementation must be perfectly aligned with the Java side fields.
