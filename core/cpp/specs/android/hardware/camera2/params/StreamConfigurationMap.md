# StreamConfigurationMap - Reverse Engineering Documentation

## Executive Summary
`StreamConfigurationMap` is an immutable class that provides the authoritative list of all supported output and input stream configurations for a camera device. It includes supported image formats, resolutions, and their associated timing information (minimum frame durations and stall durations). It is the primary tool for applications to determine how to configure `Surface` objects for a capture session.

## Architecture Overview
- **Storage**: Internal arrays of `StreamConfiguration` and `StreamConfigurationDuration` objects.
- **Categorization**: Separates configurations by data space (Color, Depth, Dynamic Depth, HEIC, JPEG/R).
- **High Speed**: Includes specialized configurations for high-speed video recording (e.g., 120/240 fps).
- **Reprocessing**: Provides valid output formats for given input formats.

## Detailed Functionality

### Resolution Discovery
**Purpose**: To find available sizes for a desired format.
**Algorithm**:
1. Application calls `getOutputSizes(int format)`.
2. The map filters the internal `mConfigurations` list for matching format and `isOutput == true`.
3. Returns an array of `Size` objects.

### Timing Information
**Purpose**: To calculate the maximum possible frame rate.
**Definitions**:
- **Min Frame Duration**: The absolute minimum time between two consecutive frames of a single stream.
- **Stall Duration**: Extra time added to the pipeline when a specific format/size is captured (common for JPEG/RAW).
**Algorithm**: `Total Frame Time = Max(Min Frame Durations of all targets) + Stall Duration`.

### Input/Output Mapping
**Purpose**: To support image reprocessing (YUV/Opaque -> JPEG).
**Algorithm**: `getValidOutputFormatsForInput(int inputFormat)` returns the allowed destination formats for a reprocess request.

## Data Model

### Internal Mappings
- `mOutputFormats`: Mapping of format to count of "normal" (>= 20fps) output sizes.
- `mHighResOutputFormats`: Mapping of format to count of "slow" high-resolution sizes.
- `mInputFormats`: Supported formats for input streams.
- `mDepthOutputFormats`, `mHeicOutputFormats`, etc.: Specialized format maps.

### Constants
- `HAL_PIXEL_FORMAT_BLOB`: 0x21 (used for JPEG, HEIC).
- `HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED`: 0x22 (used for SurfaceView/MediaRecorder).
- `DURATION_20FPS_NS`: 50,000,000 ns (boundary for high-res classification).

## API Reference

### Public Methods
- `int[] getOutputFormats()`: List all supported output formats.
- `Size[] getOutputSizes(int format)`: Get resolutions for a format.
- `long getOutputMinFrameDuration(int format, Size size)`: Get base timing.
- `long getOutputStallDuration(int format, Size size)`: Get extra stall timing.
- `Size[] getHighSpeedVideoSizes()`: Get sizes supporting high-speed.
- `Range<Integer>[] getHighSpeedVideoFpsRangesFor(Size size)`: Get FPS ranges for a high-speed size.

## Java-to-C++ Translation Guide

### Format Handling
- **Java**: Uses `ImageFormat` and `PixelFormat`.
- **C++**: Use `android_pixel_format_t` from `system/graphics.h`. Map them to a C++ enum for safety.

### Collection Types
- **Java**: Uses `SparseIntArray` and `HashMap`.
- **C++**: Use `std::map<int, int>` or `std::vector<std::pair<int, int>>`. For performance, a flattened array of configuration structs is preferred.

### Memory Management
- **Java**: The constructor takes ownership of large arrays.
- **C++**: The native equivalent (`android::StreamConfigurationMap`) should store these values in a contiguous memory block or use `std::vector` for flexibility.

## Test Cases & Validation
1. **Implementation Defined**: Verify that `getOutputSizes(ImageFormat.PRIVATE)` (Implementation Defined) always returns at least one size.
2. **Timing Consistency**: Ensure `getOutputMinFrameDuration` returns 0 for devices not supporting manual sensor control.
3. **High Speed Compatibility**: Verify that high-speed sizes are a subset of normal output sizes.

## Implementation Risks
- **Complexity**: The logic for filtering high-res vs. normal resolution based on the 20fps threshold is subtle and must be implemented exactly as in Java to ensure API consistency.
- **Dataspace Ambiguity**: Many public formats (JPEG, HEIC, Depth) map to the same internal `HAL_PIXEL_FORMAT_BLOB`. The `dataspace` field is critical for disambiguation.
