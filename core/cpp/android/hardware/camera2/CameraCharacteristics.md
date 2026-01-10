# CameraCharacteristics - Reverse Engineering Documentation

## Executive Summary
`CameraCharacteristics` is a core component of the Android Camera2 API that provides static metadata about a camera device. It acts as a read-only repository of capabilities, fixed hardware parameters, and available settings for a specific camera ID. It is essential for application initialization, capability discovery, and understanding the physical constraints of the camera hardware.

## Architecture Overview
- **Inheritance**: Extends `CameraMetadata<CameraCharacteristics.Key<?>>`.
- **Key-Value Store**: Implements a type-safe key-value store where keys are of type `CameraCharacteristics.Key<T>`.
- **Initialization**: Obtained via `CameraManager.getCameraCharacteristics(String cameraId)`.
- **Immutability**: The object is immutable once retrieved.

## Detailed Functionality

### Metadata Retrieval
**Purpose**: To provide applications with details about the camera's fixed properties.
**Algorithm**:
1. Application calls `get(Key<T> key)`.
2. The internal `CameraMetadataNative` object is queried for the value associated with the key.
3. If the key is a "synthetic" key, a specialized getter method may be used to reconstruct the high-level object from raw metadata.
4. Returns the value of type `T`, or `null` if the key is not available on the device.

### Synthetic Key Handling
**Purpose**: To provide convenient high-level objects (like `StreamConfigurationMap`) that are backed by multiple raw metadata tags.
**Java-Specific Notes**: Uses `TypeReference` to preserve generic type information at runtime for keys.

## Data Model

### CameraCharacteristics.Key<T>
- **Name**: The string name of the metadata tag (e.g., `android.lens.facing`).
- **Type**: The class or `TypeReference` of the value type `T`.

### Key Categories
- **Control**: Available modes for auto-exposure, auto-focus, etc.
- **Lens**: Focal length, aperture, lens facing direction.
- **Sensor**: Pixel array size, sensitivity range, timestamp source.
- **Request**: Max number of output streams, pipeline depth.
- **Info**: Hardware level (`LEGACY`, `LIMITED`, `FULL`, `LEVEL_3`), version.

## API Reference

### Public Methods
- `T get(Key<T> key)`: Retrieve a characteristic value.
- `List<Key<?>> getKeys()`: Get all keys supported by the device.
- `List<CaptureRequest.Key<?>> getAvailableCaptureRequestKeys()`: Keys that can be used in a `CaptureRequest`.
- `List<CaptureResult.Key<?>> getAvailableCaptureResultKeys()`: Keys that will be present in a `CaptureResult`.
- `List<CaptureRequest.Key<?>> getAvailableSessionKeys()`: Keys that can be used to initialize a capture session.
- `List<CaptureRequest.Key<?>> getAvailablePhysicalCameraRequestKeys()`: Keys for physical cameras in a logical multi-camera setup.

## Java-to-C++ Translation Guide

### Key Implementation
- **Java**: `public static final Key<Integer> SENSOR_ORIENTATION = new Key<>("android.sensor.orientation", int.class);`
- **C++**: Use a template class `Key<T>` with a static identifier or string name. Use `std::type_index` or similar for type safety if needed.

### Storage
- **Java**: `CameraMetadataNative` (JNI wrapper around C++ `CameraMetadata` object).
- **C++**: Can directly use `android::CameraMetadata` from the native framework.

### Memory Management
- **Java**: GC managed.
- **C++**: `CameraCharacteristics` should be a value type or managed by `std::shared_ptr` as it's typically shared across the app.

## Test Cases & Validation
1. **Capability Check**: Verify `INFO_SUPPORTED_HARDWARE_LEVEL` returns one of the defined constants.
2. **Stream Configuration**: Ensure `SCALER_STREAM_CONFIGURATION_MAP` returns a non-null object containing valid sizes for the device.
3. **Lens Facing**: Check that `LENS_FACING` returns `FRONT`, `BACK`, or `EXTERNAL`.

## Implementation Risks
- **Hardware Variation**: Different devices support vastly different subsets of keys. The C++ implementation must gracefully handle missing keys.
- **Synthetic Keys**: Reimplementing the logic for complex types like `StreamConfigurationMap` requires careful mapping to multiple underlying native tags.
- **Binary Compatibility**: Ensure the tag IDs match the values expected by the camera HAL.
