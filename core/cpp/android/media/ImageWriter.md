# ImageWriter - Reverse Engineering Documentation

## Executive Summary
`ImageWriter` allows an application to produce `Image` data into a `Surface`. It acts as a producer, allowing downstream components (like `CameraDevice` input) to consume images.

## Architecture Overview
- **Producer**: Writes to a destination `Surface`.
- **Zero-Copy**: Supports queuing images directly from an `ImageReader` without copying data.
- **Queueing**: `dequeueInputImage()` gets a free buffer, `queueInputImage()` sends it downstream.

## Detailed Functionality

### Initialization
- **`newInstance(...)`**: Creates an `ImageWriter` connected to a destination `Surface`.

### Operation
- **`dequeueInputImage()`**: blocking call to get a free buffer from the Surface's queue. Returns a `WriterSurfaceImage` (implementation of `Image`).
- **`queueInputImage(Image)`**: Submits the image to the consumer. Can handle images dequeued from this writer *or* images detached from an `ImageReader` (zero-copy migration).

### Listeners
- **`OnImageReleasedListener`**: Callback when the downstream consumer is done with a buffer and returns it to the writer.

## Java-to-C++ Translation Guide
- **Native Core**: Wraps a native `ImageWriter` (likely based on `ANativeWindow` or `IGraphicBufferProducer`).
- **Buffer Migration**: The logic for taking an `Image` from `ImageReader` and attaching it to `ImageWriter` involves intricate native buffer handle passing.

## Source Reference
Defined in `ImageWriter.java`.
