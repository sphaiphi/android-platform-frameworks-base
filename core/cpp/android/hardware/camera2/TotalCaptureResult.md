# TotalCaptureResult - Reverse Engineering Documentation

## Executive Summary
`TotalCaptureResult` is the complete representation of a capture result. Unlike its parent `CaptureResult`, which may contain only a subset of metadata (partial results), `TotalCaptureResult` is guaranteed to contain the fully assembled metadata for a frame, including all results from physical cameras in a logical multi-camera setup.

## Architecture Overview
- **Inheritance**: Extends `CaptureResult`.
- **Composition**:
    - `List<CaptureResult> mPartialResults`: The sequence of partial results that were merged into this total result.
    - `Map<String, TotalCaptureResult> mPhysicalCaptureResults`: A map of results for each physical camera involved in the capture.
- **Initialization**: Created by the `CameraDevice` implementation when all metadata for a request has been collected from the HAL.
- **Immutability**: Inherits immutability from `CaptureResult`.

## Detailed Functionality

### Result Assembly
**Purpose**: To provide a unified view of all metadata associated with a single frame.
**Algorithm**:
1. The camera HAL may send metadata in multiple chunks (partial results).
2. The `CameraDevice` collects these chunks.
3. Once the final chunk is received, a `TotalCaptureResult` is constructed by merging all chunks.
4. If it's a logical camera, results from active physical cameras are also collected and added to the `mPhysicalCaptureResults` map.

### Physical Camera Metadata
**Purpose**: To provide access to sensor-specific metadata (like raw sensitivity) for physical cameras in a logical group.
**Java-Specific Notes**: Applications use `getPhysicalCameraTotalResults()` to access this map. This is essential for features like multi-lens bokeh or ultra-wide/telephoto switching.

## Data Model

### Members
- `partialResults`: Unmodifiable list of the `CaptureResult` objects that preceded this total result.
- `physicalCaptureResults`: Mapping of physical camera ID to the corresponding `TotalCaptureResult`.
- `sessionId`: The ID of the `CameraCaptureSession` that produced this result.

## API Reference

### Public Methods
- `List<CaptureResult> getPartialResults()`: Retrieve the partial results used for assembly.
- `Map<String, TotalCaptureResult> getPhysicalCameraTotalResults()`: Get metadata for physical cameras.
- `int getSessionId()`: Get the originating session ID.

## Java-to-C++ Translation Guide

### Aggregation Logic
- **Java**: Merging happens in `CameraDeviceImpl`.
- **C++**: The `CaptureResult` implementation should support a `merge()` or `append()` operation that combines metadata from multiple `android::CameraMetadata` blobs.

### Memory Optimization
- **Java**: Stores a list of partial results, which can be memory-intensive.
- **C++**: Since `TotalCaptureResult` is the final state, you might want to discard the partial results after merging to save memory, unless the user explicitly requests them.

### Mapping
- **Java**: `HashMap<String, TotalCaptureResult>`.
- **C++**: `std::map<std::string, std::shared_ptr<TotalCaptureResult>>` or a more efficient flat map.

## Test Cases & Validation
1. **Completeness**: Verify that all keys from `getAvailableCaptureResultKeys()` return non-null values in a `TotalCaptureResult` if they were requested.
2. **Physical Result Mapping**: On a logical multi-camera device, verify that the keys in `getPhysicalCameraTotalResults()` match the IDs returned by `CameraCharacteristics.getPhysicalCameraIds()`.
3. **Partial Order**: Ensure that partial results in the list are in the correct chronological order of receipt.

## Implementation Risks
- **Metadata Size**: Combining metadata from multiple cameras for every frame (at 30-60fps) generates significant data volume. Efficient memory pooling for metadata objects is recommended.
- **Inconsistency**: Ensure that the `frameNumber` and `timestamp` are consistent across the logical result and all its physical results.