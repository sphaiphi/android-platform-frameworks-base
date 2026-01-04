# ImageUtils - Reverse Engineering Documentation

## Executive Summary
`ImageUtils` provides package-private utility methods for handling `Image` objects, formats, and native memory estimations.

## Detailed Functionality

### Plane Calculation
- **`getNumPlanesForFormat(int)`**: Returns the number of planes for a given `ImageFormat` or `PixelFormat` (e.g., 3 for YUV, 1 for JPEG).
- **`getNumPlanesForHardwareBufferFormat(int)`**: Same as above but for `HardwareBuffer` formats.

### Image Copying
- **`imageCopy(Image src, Image dst)`**: Copies pixel data between compatible images. Handles direct buffer copying or row-by-row copying if strides differ. Validates formats and sizes.

### Memory Estimation
- **`getEstimatedNativeAllocBytes(...)`**: estimates the native memory footprint based on dimensions and format. Used for VM GC accounting.

## Java-to-C++ Translation Guide
- **Format Logic**: The switch cases for plane counts are logic that would likely be duplicated in C++ image handling utilities.
- **Memory Copy**: `imageCopy` logic (handling strides) is a standard image processing routine (`memcpy` or `copy_if`).

## Source Reference
Defined in `ImageUtils.java`.
