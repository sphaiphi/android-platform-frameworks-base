# DngCreator.java - Reverse Engineering Documentation

## Executive Summary
`DngCreator` provides functionality to write raw pixel data (typically from `RAW_SENSOR` format) into a Digital Negative (DNG) file. It handles the generation of TIFF/EP compatible metadata from `CameraCharacteristics` and `CaptureResult`.

## Architecture Overview
- **Type**: Utility Class
- **Package**: `android.hardware.camera2`
- **Implements**: `AutoCloseable`.
- **Dependencies**: Native implementation (`nativeWriteImage`, etc.).

## Detailed Functionality

### Metadata Generation
-   Automatically calculates time offsets between sensor timestamps and wall clock time.
-   Converts coordinates to EXIF GPS tag format.
-   Generates TIFF orientation tags.

### Writing Methods
-   `writeInputStream`: Writes from a raw stream.
-   `writeByteBuffer`: Writes from a buffer (handles strides and offsets).
-   `writeImage`: High-level wrapper for `android.media.Image`.

### Processing
-   Includes internal YUV-to-RGB and Color-to-RGB conversion logic for thumbnail generation.

## Java-to-C++ Translation Guide
This class is primarily a wrapper for native code. The real work is done in the C++ layer.

### Native Interface
The class defines several `native` methods:
-   `nativeInit`, `nativeDestroy`
-   `nativeSetOrientation`, `nativeSetDescription`, `nativeSetGpsTags`
-   `nativeWriteImage`, `nativeWriteInputStream`

Porting this would involve exposing the underlying `libimg_utils` or similar internal DNG writing library.
