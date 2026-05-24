# MeteringRectangle - Reverse Engineering Documentation

## Executive Summary
`MeteringRectangle` defines a weighted rectangular region on the camera sensor used for metering calculations (Auto-Exposure, Auto-Focus, and Auto-White Balance). Applications can specify multiple regions to guide the camera's algorithms toward specific areas of interest in the scene.

## Architecture Overview
- **Storage**: Immutable data class.
- **Coordinate System**: Based on the sensor's active pixel array (`SENSOR_INFO_ACTIVE_ARRAY_SIZE`). `(0,0)` is top-left.
- **Usage**: Set via `CaptureRequest.CONTROL_AE_REGIONS`, `CONTROL_AF_REGIONS`, and `CONTROL_AWB_REGIONS`.

## Detailed Functionality

### Weighting Logic
**Purpose**: To determine the relative importance of a region.
**Details**:
- The `weight` ranges from `0` to `1000`.
- A weight of `0` means the region is ignored.
- A larger area with the same weight as a smaller one has more total influence because the weight is "per pixel".
- Overlapping rectangles have their weights summed in the overlapping area.

### Boundary Handling
**Purpose**: To handle regions that fall outside the current field of view.
**Algorithm**: If a metering rectangle extends beyond the `scaler.cropRegion` used for the current frame, the camera device ignores the portions outside the crop region.

## Data Model

### Members
- `mX`, `mY` (`int`): Top-left coordinates.
- `mWidth`, `mHeight` (`int`): Dimensions of the region.
- `mWeight` (`int`): Influence factor (0-1000).

## API Reference

### Public Methods
- `int getX()`, `getY()`, `getWidth()`, `getHeight()`: Geometry accessors.
- `int getMeteringWeight()`: Weight accessor.
- `Rect getRect()`: Returns the geometry as a standard `Rect` object.
- `Size getSize()`: Returns the dimensions as a `Size` object.

### Constants
- `METERING_WEIGHT_MIN`: `0`.
- `METERING_WEIGHT_MAX`: `1000`.
- `METERING_WEIGHT_DONT_CARE`: `0`.

## Java-to-C++ Translation Guide

### Data Structure
- **Java**: Uses multiple constructors taking `Rect`, `Point`, etc.
- **C++**: Provide a single canonical struct/class. Use `int32_t` for coordinates and weight.

### Validation
- **Java**: Uses `com.android.internal.util.Preconditions` to enforce non-negative values and ranges.
- **C++**: Enforce invariants in the constructor using `assert` (for debug) and runtime checks that return `std::expected` or throw if appropriate for the project style.

## Test Cases & Validation
1. **Overlap Test**: Define two overlapping rectangles and verify that the combined influence area behaves as expected (e.g., focus locks on the intended subject).
2. **Out-of-Bounds Test**: Define a rectangle that is completely outside the sensor array and ensure it is ignored without causing errors.
3. **Zero Weight**: Verify that setting all regions to weight `0` allows the camera to perform default global metering.
