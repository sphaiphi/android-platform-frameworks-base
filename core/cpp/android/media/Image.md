# Image - Reverse Engineering Documentation

## Executive Summary
`Image` is an abstract class representing a single complete image buffer, primarily used with low-level media APIs like `MediaCodec`, `CameraDevice`, and `ImageReader`. It provides direct access to pixel data via `ByteBuffer`s, enabling efficient processing. Unlike `Bitmap`, it is not a UI resource and must be closed to release underlying hardware resources.

## Architecture Overview
- **Abstraction**: Wraps native image buffers.
- **Components**: Composed of one or more `Plane` objects.
- **Resource Management**: Implements `AutoCloseable`. Efficient resource usage requires explicit closing.

## Detailed Functionality

### Core Properties
- **Format**: Describes the pixel layout (e.g., YUV_420_888, JPEG, RAW_SENSOR).
- **Dimensions**: Width and height in pixels.
- **Timestamp**: Time associated with the frame (nanoseconds).
- **Crop Rect**: Region of valid pixels.

### Data Access
- **`getPlanes()`**: Returns an array of `Plane` objects.
- **`Plane`**: Inner class providing access to pixel data.
    - `getBuffer()`: Direct `ByteBuffer` for pixel data.
    - `getRowStride()`: Bytes between rows.
    - `getPixelStride()`: Bytes between pixels.

### Synchronization
- **`getFence()` / `setFence()`**: Supports `SyncFence` for synchronization with hardware components.

### Hardware Interop
- **`getHardwareBuffer()`**: Access to the underlying `HardwareBuffer` (if supported).

## Java-to-C++ Translation Guide
- **Buffer Mapping**: `Plane.getBuffer()` corresponds to mapping a specific plane of a native buffer (e.g., `AHardwareBuffer_lock`).
- **Strides**: `rowStride` and `pixelStride` map to standard image buffer stride concepts.
- **Life Cycle**: `close()` maps to unlocking/releasing the native buffer.

## Source Reference
Defined in `Image.java`.
