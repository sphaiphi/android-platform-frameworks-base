# Surface - Reverse Engineering Documentation

## Executive Summary
`Surface` is a handle to a raw buffer that is being managed by the system compositor (SurfaceFlinger). It acts as a producer-consumer link: one component (the producer, e.g., a `ViewRootImpl` or `MediaPlayer`) draws into it, while another component (the consumer, e.g., the display or a `SurfaceTexture`) displays it.

## Architecture Overview
*   **Role**: Buffer handle for the graphics pipeline.
*   **JNI Centric**: Most operations are implemented in native code (`android_view_Surface.cpp`).
*   **Key Native Object**: `ANativeWindow` (C++) or `IGraphicBufferProducer` (Binder).
*   **Life Cycle**: Managed by `CloseGuard`. Must be released explicitly to free native graphics buffers.

## Detailed Functionality

### 1. Canvas Rendering
*   **`lockCanvas(Rect)`**: Returns a `Canvas` for software-based drawing into the surface buffer. Locks the buffer until `unlockCanvasAndPost` is called.
*   **`lockHardwareCanvas()`**: Returns a hardware-accelerated canvas (linked to the GPU).

### 2. Composition Link
*   **`unlockCanvasAndPost(Canvas)`**: Commits the finished drawing to the buffer queue, triggering the consumer (SurfaceFlinger) to update the display.

### 3. SurfaceControl Integration
*   **`copyFrom(SurfaceControl)`**: Links this surface handle to a specific layer in the system compositor.

### 4. Advanced Features
*   **Frame Rate**: `setFrameRate()` allows apps to hint the desired refresh rate for this surface.
*   **Scaling**: `setScalingMode()` controls how buffers are stretched to fit the surface bounds.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `sp<Surface>` or `ANativeWindow*`.
*   **Parceling**: Serialization MUST be bit-for-bit compatible with `frameworks/native/libs/gui/Surface.cpp`.
*   **Error Handling**: Use `OutOfResourcesException` for allocation failures.

## Implementation Risks
*   **Buffer Starvation**: Failing to call `unlockCanvasAndPost` will cause the producer to hang waiting for an available buffer.
*   **Native Leaks**: `mNativeObject` points to a heavy-weight C++ `Surface` instance. Failing to `release()` will quickly lead to system-wide graphics memory exhaustion.
*   **Thread Safety**: While the `Surface` object is thread-safe for some operations, the `Canvas` returned by `lockCanvas` is NOT.
