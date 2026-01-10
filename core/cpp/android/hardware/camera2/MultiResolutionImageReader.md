# MultiResolutionImageReader.java - Reverse Engineering Documentation

## Executive Summary
`MultiResolutionImageReader` manages a group of `ImageReader` objects of the same format but different sizes. It is designed for logical multi-cameras (optical zoom) or ultra-high-resolution sensors where the output resolution can change dynamically based on zoom or lighting.

## Architecture Overview
- **Type**: Management Class
- **Package**: `android.hardware.camera2`
- **Implements**: `AutoCloseable`.
- **Relationship**: Wraps multiple `android.media.ImageReader` instances.

## Detailed Functionality
-   **Dynamic Selection**: The camera device decides which internal `ImageReader` receives the data.
-   **Surface Access**: 
    -   `getSurface()`: Returns a "primary" surface used as a target in `CaptureRequest`.
    -   `getSurface(Size, String)`: Returns a specific internal surface for session configuration.
-   **Image Acquisition**: Apps use the `ImageReader` object passed to the `onImageAvailable` callback to acquire frames.

## Java-to-C++ Translation Guide
This is a composite object. In C++, it should maintain a map of sizes to native `ImageReader` equivalents.

```cpp
class MultiResolutionImageReader {
    std::vector<std::unique_ptr<NativeImageReader>> mReaders;
    // ...
};
```
