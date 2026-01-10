# CaptureResult - Reverse Engineering Documentation

## Executive Summary
`CaptureResult` represents the outcome of a single image capture. It contains the metadata describing the state of the camera hardware and processing pipeline at the moment the capture occurred, as well as the output of various algorithms (AE, AF, face detection, etc.).

## Architecture Overview
- **Inheritance**: Extends `CameraMetadata<CaptureResult.Key<?>>`.
- **Derived Classes**: `TotalCaptureResult` (complete result), `CaptureResult` (can represent partial results).
- **Initialization**: Provided by `CameraCaptureSession.CaptureCallback` methods (`onCaptureStarted`, `onCaptureProgressed`, `onCaptureCompleted`).
- **Immutability**: `CaptureResult` objects are immutable.

## Detailed Functionality

### Metadata Retrieval
**Purpose**: To allow applications to inspect the final state of the camera for a specific frame.
**Algorithm**:
1. Application receives a `CaptureResult` via a callback.
2. Application calls `get(Key<T> key)`.
3. The internal `CameraMetadataNative` is queried.
4. Returns the actual value used/determined by the camera (e.g., the actual exposure time used if auto-exposure was on).

### Partial vs. Total Results
**Purpose**: To allow low-latency access to some metadata (like AF state) before the entire capture is finished.
**Algorithm**:
1. The camera HAL may send "partial" results as soon as some metadata is ready.
2. `onCaptureProgressed` is called with a `CaptureResult`.
3. Finally, `onCaptureCompleted` is called with a `TotalCaptureResult`, which combines all partial results and the final metadata.

## Data Model

### CaptureResult.Key<T>
- **Name**: The string name of the result tag (e.g., `android.control.afState`).
- **Type**: The class or `TypeReference` of the value type `T`.

### Key Categories
- **Control States**: `aeState`, `afState`, `awbState`.
- **Actual Settings**: `exposureTime`, `sensitivity`, `focalLength`.
- **Statistics**: `faces` (face detection), `lensShadingMap`, `sceneFlicker`.
- **Sensor Info**: `timestamp`, `rollingShutterSkew`.

## API Reference

### Public Methods
- `T get(Key<T> key)`: Retrieve a result value.
- `List<Key<?>> getKeys()`: Get all keys present in this result.
- `CaptureRequest getRequest()`: Get the `CaptureRequest` that produced this result.
- `long getFrameNumber()`: Get the unique frame number for this capture.
- `int getSequenceId()`: Get the sequence ID for the request burst.

## Java-to-C++ Translation Guide

### State Tracking
- **Java**: States are returned as `Integer` constants (e.g., `CaptureResult.CONTROL_AF_STATE_FOCUSED_LOCKED`).
- **C++**: Use `enum class` for all state constants to provide better type safety.

### Metadata Storage
- **Java**: `CameraMetadataNative`.
- **C++**: Directly use `android::CameraMetadata`. Ensure it is passed by `const` reference or `std::shared_ptr` to avoid copies.

### Partial Result Handling
- **Java**: Partial results are `CaptureResult` objects; the final is `TotalCaptureResult`.
- **C++**: Implement a similar hierarchy or a flag within a single `CaptureMetadata` class to indicate completeness.

## Test Cases & Validation
1. **AE Convergence**: Verify that `CONTROL_AE_STATE` eventually reaches `CONVERGED` or `LOCKED` when AE is active.
2. **Timestamp Monotonicity**: Ensure that `SENSOR_TIMESTAMP` increases for successive frame numbers.
3. **Face Detection**: Verify that `STATISTICS_FACES` returns data when `STATISTICS_FACE_DETECT_MODE` was enabled in the request.

## Implementation Risks
- **Synchronization**: Matching partial results to the correct frame number and request ID must be handled carefully.
- **Accuracy**: Some metadata values (like lens shading maps) can be large; ensure efficient memory handling and avoid unnecessary allocations.
- **Availability**: Not all keys are available in every result (especially partial ones). The C++ API must handle `std::nullopt` or similar for missing keys.
