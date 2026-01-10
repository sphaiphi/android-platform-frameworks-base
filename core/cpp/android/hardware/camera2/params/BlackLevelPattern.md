# BlackLevelPattern - Reverse Engineering Documentation

## Executive Summary
`BlackLevelPattern` is an immutable class that stores a 2x2 grid of integer offsets used for black level compensation. These offsets represent the "dark signal" or noise floor for each of the four color channels in a Bayer RAW pattern, which must be subtracted from the raw values to ensure that "true black" in the scene corresponds to a value of 0 in the processed image.

## Architecture Overview
- **Storage**: A 4-element integer array.
- **Pattern**: 2x2 grid corresponding to the sensor's Color Filter Arrangement (CFA).
- **Usage**: Query static values via `CameraCharacteristics.SENSOR_BLACK_LEVEL_PATTERN` or dynamic per-frame values via `CaptureResult.SENSOR_DYNAMIC_BLACK_LEVEL`.

## Detailed Functionality

### Offset Mapping
**Purpose**: To map a pixel's (x, y) coordinates to its specific color channel's black level.
**Algorithm**:
The offset for a pixel at `(column, row)` is determined by:
`index = ((row % 2) << 1) | (column % 2)`
`offset = mCfaOffsets[index]`

### Monochromatic Support
**Java-Specific Notes**: For monochrome sensors, all four elements in the 2x2 pattern are required to be identical.

## Data Model

### Members
- `mCfaOffsets` (`int[]`): Array of 4 offsets in row-major order: `[top-left, top-right, bottom-left, bottom-right]`.

## API Reference

### Public Methods
- `int getOffsetForIndex(int column, int row)`: Coordinate-aware accessor.
- `void copyTo(int[] destination, int offset)`: Flat array export.

## Java-to-C++ Translation Guide

### Data Structure
- **Java**: `int[]` of size 4.
- **C++**: `std::array<int32_t, 4>`.

### Bitwise Logic
- **Java**: `((row & 1) << 1) | (column & 1)`.
- **C++**: This logic is highly efficient and should be used directly in a `get_offset(x, y)` method.

## Test Cases & Validation
1. **Grid Wrapping**: Verify that `getOffsetForIndex(0, 0)` and `getOffsetForIndex(2, 2)` return the same value.
2. **Channel Assignment**: Verify that the indices match the `SENSOR_INFO_COLOR_FILTER_ARRANGEMENT` (e.g., for RGGB, index 0 is R, 1 is G_even, 2 is G_odd, 3 is B).
3. **Range Check**: Ensure offsets are non-negative.
埋
## Implementation Risks
- **Pattern Alignment**: If the sensor uses a non-standard 2x2 pattern (unlikely in modern Android), the indexing logic might need adjustment.
- **Dynamic Updates**: Some high-end sensors update black levels dynamically based on temperature; the C++ implementation must efficiently handle per-frame updates from the metadata.
