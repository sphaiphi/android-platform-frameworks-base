# CaptureRequest - Reverse Engineering Documentation

## Executive Summary
`CaptureRequest` is the primary object used to configure the camera hardware and processing pipeline for a single image capture or a sequence of captures. It encapsulates all the settings (exposure, focus, flash, etc.) and the target output surfaces for the capture operation.

## Architecture Overview
- **Inheritance**: Extends `CameraMetadata<CaptureRequest.Key<?>>`.
- **Composition**: Contains a set of output `Surface` objects and a `CameraMetadataNative` object for settings.
- **Builder Pattern**: Created using `CaptureRequest.Builder`, which is obtained from `CameraDevice.createCaptureRequest(int templateType)`.
- **Immutability**: Once built, a `CaptureRequest` is immutable.

## Detailed Functionality

### Builder Pattern
**Purpose**: To allow step-by-step configuration of a capture request.
**Algorithm**:
1. `CameraDevice` provides a `Builder` with default settings based on a template (e.g., `TEMPLATE_PREVIEW`, `TEMPLATE_STILL_CAPTURE`).
2. Application calls `set(Key<T> key, T value)` to modify settings.
3. Application calls `addTarget(Surface surface)` to specify output destinations.
4. Application calls `build()` to produce an immutable `CaptureRequest`.

### Setting Propagation
**Purpose**: To communicate the desired state to the camera HAL.
**Java-Specific Notes**: Settings are stored in `CameraMetadataNative`, which is passed across the JNI boundary to the native camera service.

## Data Model

### CaptureRequest.Key<T>
- **Name**: The string name of the control tag (e.g., `android.control.aeMode`).
- **Type**: The class or `TypeReference` of the value type `T`.

### Key Categories
- **Control**: AE, AF, AWB modes and triggers.
- **Edge**: Edge enhancement modes.
- **Flash**: Flash firing and power levels.
- **Lens**: Aperture, focal length, focus distance.
- **Noise Reduction**: NR modes and strengths.
- **Scaler**: Digital zoom crop region.
- **Sensor**: Exposure time, sensitivity (ISO), frame duration.

## API Reference

### Public Methods
- `T get(Key<T> key)`: Retrieve a setting value.
- `List<Key<?>> getKeys()`: Get all settings defined in this request.
- `Object getTag()`: Get an optional application-defined tag for identifying results.
- `boolean isReprocess()`: Returns true if this is a request for reprocessing.

### Builder Methods
- `void addTarget(Surface outputTarget)`: Add a surface as a target for this request.
- `void removeTarget(Surface outputTarget)`: Remove a target.
- `void set(Key<T> key, T value)`: Set a specific control value.
- `<T> T get(Key<T> key)`: Get the current value of a key in the builder.
- `CaptureRequest build()`: Create the immutable request object.

## Java-to-C++ Translation Guide

### Surface Management
- **Java**: Uses `android.view.Surface`.
- **C++**: Use `sp<IGraphicBufferProducer>` or `ANativeWindow*` to represent the output buffers.

### Builder Implementation
- **Java**: `CaptureRequest.Builder` maintains a `CameraMetadataNative` object.
- **C++**: A C++ `Builder` class should manage an `android::CameraMetadata` object and a `std::vector` of output targets.

### Memory Management
- **Java**: Surfaces are managed via references; metadata is JNI-backed.
- **C++**: Use `sp<>` for surfaces and `std::unique_ptr` or value semantics for `CaptureRequest` to ensure proper lifetime management.

## Test Cases & Validation
1. **Template Default**: Verify that a request created from `TEMPLATE_PREVIEW` has `CONTROL_AF_MODE` set to `CONTINUOUS_PICTURE`.
2. **Target Validation**: Ensure `build()` throws an exception if no targets are added.
3. **Immutability**: Verify that modifying the `Builder` after calling `build()` does not change the already built `CaptureRequest`.

## Implementation Risks
- **JNI Overhead**: Frequent modification of many keys in the builder can be expensive if every `set` call crosses the JNI boundary. C++ should batch metadata updates.
- **Surface Lifetimes**: Ensuring that surfaces remain valid until the capture is complete is critical to avoid crashes or leaks.
