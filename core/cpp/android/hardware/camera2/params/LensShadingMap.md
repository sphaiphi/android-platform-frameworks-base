# LensShadingMap - Reverse Engineering Documentation

## Executive Summary
`LensShadingMap` is an immutable class that describes a grid of gain factors used to correct lens vignetting and color shading. It provides a 4-channel (RGGB) gain map that is typically applied to RAW image data to ensure uniform brightness and color across the frame.

## Architecture Overview
- **Storage**: A packed float array representing a 2D grid of gain factors.
- **Dimensions**: Defined by `rows` and `columns`, usually around 30-40 in each dimension.
- **Channels**: Each grid cell contains 4 gain factors (Red, Green-Even, Green-Odd, Blue).
- **Minimum Value**: All gain factors are guaranteed to be >= 1.0.

## Detailed Functionality

### Gain Application
**Purpose**: To compensate for light fall-off at the edges of the sensor.
**Algorithm**:
1. The map is a low-resolution representation of the entire sensor.
2. For any pixel (x, y) on the sensor, the four gains are determined by bilinear interpolation between the four nearest samples in the shading map.
3. The raw pixel value is multiplied by the interpolated gain for its specific color channel.

### Monochromatic Support
**Java-Specific Notes**: For monochrome cameras, all four channel gains at any given grid position are identical.

## Data Model

### Members
- `mRows`, `mColumns` (`int`): Grid dimensions.
- `mElements` (`float[]`): Flattened array of gains in row-major order. Total size = `rows * columns * 4`.

## API Reference

### Public Methods
- `int getRowCount()`, `getColumnCount()`: Grid size.
- `float getGainFactor(int colorChannel, int column, int row)`: Individual gain accessor.
- `RggbChannelVector getGainFactorVector(int column, int row)`: 4-channel vector accessor.
- `void copyGainFactors(float[] destination, int offset)`: Bulk export.

## Java-to-C++ Translation Guide

### Memory Efficiency
- **Java**: Stores a large float array.
- **C++**: Use a contiguous `std::vector<float>` or a custom `ShadingGrid` class. Given that these maps are generated for every frame, consider using a pool of pre-allocated buffers.

### Interpolation Helper
- **Java**: The class only provides point access.
- **C++**: Adding a `getInterpolatedGains(float normalizedX, float interpolatedY)` method would be highly beneficial for developers implementing the actual correction logic.

## Test Cases & Validation
1. **Identity Map**: Verify that an all-1.0 map results in no change to image brightness.
2. **Bounds Check**: Ensure that accessing row/column indices at the exact grid boundaries does not cause crashes.
3. **Array Packing**: Verify that `copyGainFactors` maintains the row-major, interleaved channel order expected by HAL.
