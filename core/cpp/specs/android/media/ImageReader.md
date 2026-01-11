# ImageReader - Reverse Engineering Documentation

## Executive Summary
`ImageReader` allows direct application access to image data rendered into a `Surface`. It acts as a consumer of image buffers produced by camera, video decoders, etc.

## Architecture Overview
- **Producer-Consumer**: Provides a `Surface` that producers render into. `ImageReader` consumes these frames as `Image` objects.
- **Queue**: Manages a queue of image buffers (up to `maxImages`).
- **JNI**: Heavily relies on native code (`media_jni`) for buffer management.

## Detailed Functionality

### Initialization
- **`newInstance(...)`**: Factory methods to create an `ImageReader` with specific dimensions, format, and capacity.
- **Native Init**: Allocates a native `CpuConsumer` (or similar) mechanism.

### Acquiring Images
- **`acquireLatestImage()`**: Gets the newest frame, discarding older ones in the queue. Best for real-time.
- **`acquireNextImage()`**: Gets the next frame in the queue. Best for recording/batch processing.
- **`SurfaceImage`**: Inner class implementation of `Image` specific to `ImageReader`.

### Listeners
- **`OnImageAvailableListener`**: Callback invoked when a new frame is ready. Executed on a specified `Handler` or `Executor`.

### Resource Management
- **`close()`**: Releases the Surface and all acquired images.
- **`discardFreeBuffers()`**: Frees cached but unused buffers.

## Java-to-C++ Translation Guide
- **Native Implementation**: This class is a thin wrapper around a native `ImageReader` (likely based on `BufferQueue` consumer).
- **Callbacks**: The JNI layer posts events to the Java handler/executor.

## Source Reference
Defined in `ImageReader.java`.
