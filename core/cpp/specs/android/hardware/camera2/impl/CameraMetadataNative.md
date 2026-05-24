# CameraMetadataNative - Reverse Engineering Documentation

## Executive Summary
`CameraMetadataNative` is the low-level implementation of the Camera2 metadata system. It manages the physical storage of metadata tags and their values, handles serialization (parceling) across the Binder IPC boundary, and implements the mapping between high-level Java objects and raw native metadata types. It is the common backend for `CameraCharacteristics`, `CaptureRequest`, and `CaptureResult`.

## Architecture Overview
- **Storage**: Wraps a native C++ `CameraMetadata` object (via a `long mMetadataPtr`).
- **Marshalling**: Uses a "Marshaler" system to convert Java types (like `Rect`, `Size`, `Rational`) into binary formats compatible with the camera HAL.
- **Synthetic Keys**: Implements complex logic to provide virtual keys that are composed of multiple raw tags (e.g., `Face`, `LensShadingMap`).
- **JNI Interaction**: Relies heavily on `@FastNative` and regular JNI methods for performance-critical metadata access.

## Detailed Functionality

### Metadata Access (Get/Set)
**Purpose**: To read and write metadata tags.
**Algorithm**:
1. Check if the key is overridden in `sGetCommandMap` or `sSetCommandMap`.
2. If overridden, execute the custom `GetCommand` or `SetCommand` (e.g., `getFaces()`).
3. If not overridden, call `getBase()` or `setBase()`.
4. `getBase()` looks up the numeric tag ID, reads the raw bytes via JNI, and uses a `Marshaler` to reconstruct the Java object.

### Marshalling System
**Purpose**: To ensure cross-language and cross-process data compatibility.
**Supported Types**:
- Primitives (Byte, Int, Float, Long, Double, Rational).
- Structs (`Rect`, `Point`, `Size`, `SizeF`).
- Complex objects (`MeteringRectangle`, `ColorSpaceTransform`, `StreamConfiguration`).
- Arrays and Ranges of all the above.

### Synthetic Key Logic
**Purpose**: To provide a cleaner API for applications while keeping the HAL interface simple.
**Example (`Face`)**:
- Raw tags: `faceRectangles`, `faceScores`, `faceIds`, `faceLandmarks`.
- Synthetic key: `STATISTICS_FACES` (returns an array of `Face` objects).
- Logic: `getFaces()` reads all 4 raw tags and interleaves their data into `Face` objects.

## Data Model

### Native Types (Matching `camera_metadata.h`)
- `TYPE_BYTE` (0)
- `TYPE_INT32` (1)
- `TYPE_FLOAT` (2)
- `TYPE_INT64` (3)
- `TYPE_DOUBLE` (4)
- `TYPE_RATIONAL` (5)

## API Reference (Internal)

### Key Methods
- `native int nativeGetTagFromKeyLocal(long ptr, String name)`: Map string name to numeric tag ID.
- `native byte[] nativeReadValues(int tag, long ptr)`: Read raw data for a tag.
- `native void nativeWriteValues(int tag, byte[] values, long ptr)`: Write raw data.
- `void swap(CameraMetadataNative other)`: Efficiently transfer ownership of the native buffer.

## Java-to-C++ Translation Guide

### Implementation Strategy
- **Java**: High-level wrapper around a C++ pointer.
- **C++**: This class IS the `android::CameraMetadata`. The C++ implementation should directly use the native framework's metadata container.

### Tag Management
- **Java**: Uses string names for the first lookup, then caches IDs.
- **C++**: Use static constants for tag IDs. Ensure custom vendor tags are handled via a `VendorTagDescriptor`.

### Memory Management
- **Java**: Uses `VMRuntime.registerNativeAllocation` to inform the GC about the large native buffers.
- **C++**: Use standard RAII or `sp<CameraMetadata>` if sharing across components.

## Test Cases & Validation
1. **Parceling**: Ensure that a `CameraMetadataNative` object can be written to a `Parcel` and read back with all tags preserved.
2. **Type Safety**: Verify that trying to set an `Integer` key with a `String` value throws a compile-time or runtime error.
3. **Synthetic Mapping**: Compare the output of `getFaces()` with the values in the raw constituent tags.

## Implementation Risks
- **Endianness**: The binary format must be consistent (usually little-endian) across all processes.
- **JNI Synchronization**: Metadata objects are often accessed from multiple threads (e.g., UI and background capture threads). The C++ side must ensure thread-safe access to the underlying buffer.
- **Binary Stability**: The internal `HAL_PIXEL_FORMAT_*` and `HAL_DATASPACE_*` values must match the definitions in `system/graphics.h`.
