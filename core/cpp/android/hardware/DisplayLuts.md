# DisplayLuts - Reverse Engineering Documentation

## Executive Summary
`DisplayLuts` provides an API for developers to apply Lookup Tables (LUTs) to a `SurfaceControl`. This is used for advanced color manipulations and tonemapping, allowing applications to control how their content is rendered on the display hardware (HWC).

## Architecture Overview
The class manages a collection of `Entry` objects, each representing a 1D or 3D LUT. It tracks offsets and total data size to prepare buffers for the native display system.

## Detailed Functionality

### `Entry` Class
- **Purpose**: Holds the raw float data for a single LUT.
- **Constraints**:
    - Buffer length limit: 100,000 floats.
    - Dimension: Must be `ONE_DIMENSION` (1D) or `THREE_DIMENSION` (3D).
    - 3D LUT Verification: Buffer length must be a perfect cube multiplied by 3 (for R, G, B channels).
- **Data Organization**: 3D LUT data is normalized [0.0, 1.0] and organized in R, G, B order.

### LUT Application
- `set(Entry)`: Sets a single LUT (replaces previous).
- `set(Entry, Entry)`: Sets a 1D and a 3D LUT to be applied in sequence. The first must be 1D, the second 3D.

### Internal Data Retrieval (for Native)
- `getLutBuffers()`: Flattens all entry buffers into a single float array.
- `getOffsets()`, `getLutSizes()`, `getLutDimensions()`, `getLutSamplingKeys()`: Provide metadata arrays for the flattened buffer.

## Data Model
- **Dimension**: 1D, 3D.
- **SamplingKey**: `RGB`, `MAX_RGB`, `CIE_Y`.

## API Reference
- `public DisplayLuts()`
- `public void set(Entry entry)`
- `public void set(Entry first, Entry second)`
- `public static class Entry(...)`

## Java-to-C++ Translation Guide
- **Storage**: `ArrayList<Entry>` -> `std::vector<Entry>`.
- **Buffer Management**: `System.arraycopy` -> `std::copy` or `memcpy`.
- **Validation**: Re-implement `Math.cbrt` and dimension checks.

## Implementation Risks
- Memory consumption of large LUTs.
- Validation logic must be identical to what the Hardware Composer (HWC) expects to avoid display artifacts or driver crashes.
