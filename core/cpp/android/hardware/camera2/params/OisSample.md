# OisSample - Reverse Engineering Documentation

## Executive Summary
`OisSample` represents a single data point from the Optical Image Stabilization (OIS) system. It records the physical shift of the lens (in pixels) at a specific timestamp, allowing applications to compensate for hand shake during long exposures or to improve video stabilization in post-processing.

## Architecture Overview
- **Storage**: Immutable data class.
- **Components**: Timestamp and 2D shift (x, y).
- **Coordinate System**: Based on the sensor's pre-correction active array.
- **Frequency**: OIS samples are typically produced at a higher rate (e.g., 200Hz) than the frame rate (30-60Hz).

## Detailed Functionality

### Motion Tracking
**Purpose**: To track the lens movement relative to the sensor center.
**Shifts**:
- `xShift`: Positive values mean the lens moved from left to right.
- `yShift`: Positive values mean the lens moved from top to bottom.
- **Example**: If the optical center is at `(1000, 500)`, a shift of `(3, 5)` means the effective optical center for that sample was at `(1003, 505)`.

### Synchronization
**Java-Specific Notes**: The `timestamp` is in nanoseconds and uses the same timebase as `CaptureResult.SENSOR_TIMESTAMP`, making it easy to align OIS data with specific frames.

## Data Model

### Members
- `mTimestampNs` (`long`): Time of the sample.
- `mXShift`, `mYShift` (`float`): Lens displacement in pixels.

## API Reference

### Public Methods
- `long getTimestamp()`: Get time.
- `float getXshift()`: Get horizontal displacement.
- `float getYshift()`: Get vertical displacement.

## Java-to-C++ Translation Guide

### Data Structure
- **Java**: Simple fields.
- **C++**: A simple `struct` or `class`.
```cpp
struct OisSample {
    int64_t timestamp_ns;
    float x_shift;
    float y_shift;
};
```

### Collection Handling
- **Java**: Returned as an array in `CaptureResult.STATISTICS_OIS_SAMPLES`.
- **C++**: Use `std::vector<OisSample>`.

## Test Cases & Validation
1. **Timestamp Alignment**: Verify that the OIS sample timestamps for a frame fall within the range `[sensor_timestamp, sensor_timestamp + exposure_time + readout_time]`.
2. **Shift Finiteness**: Ensure `xShift` and `yShift` are never NaN or Infinity.
3. **Directionality**: Verify that moving the device to the right produces a negative `xShift` (as the OIS tries to move the lens to the left to compensate).
