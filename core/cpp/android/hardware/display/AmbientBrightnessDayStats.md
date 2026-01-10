# AmbientBrightnessDayStats - Reverse Engineering Documentation

## Executive Summary
`AmbientBrightnessDayStats` is a Parcelable data structure that stores aggregated ambient brightness statistics for a single day. It tracks how much time the device spent in various brightness buckets (ranges of lux values). This data is used by the system (and potentially exposed to apps with permission) to understand user lighting conditions, likely for auto-brightness optimization or battery usage analysis.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable
- **Package**: `android.hardware.display`
- **Role**: Data carrier for `DisplayManager.getAmbientBrightnessStats()`.

## Detailed Functionality

### Data Storage
- **Date**: A `LocalDate` identifying the day these stats belong to.
- **Buckets**: Defined by `float[] mBucketBoundaries`.
    - Example: `{10, 100, 1000}` defines buckets `[10, 100)`, `[100, 1000)`, `[1000, inf)`.
    - Implicit first bucket: `(-inf, 10)`? No, the `log` method checks `ambientBrightness < mBucketBoundaries[0]` and ignores it. So the first bucket starts at `mBucketBoundaries[0]`.
    - **Wait**: The JavaDoc says "if the bucket boundaries array is {b1, b2, b3}, the buckets will be [b1, b2), [b2, b3), [b3, inf)." This implies values < b1 are ignored.
- **Stats**: `float[] mStats`. Stores duration in seconds for each bucket.
    - Size must match `mBucketBoundaries`.

### Logging (Internal)
- `log(float ambientBrightness, float durationSec)`:
    - Finds the correct bucket index for the given `ambientBrightness`.
    - Adds `durationSec` to that bucket's accumulator.
    - Uses binary search (`getBucketIndex`) for efficiency.

### Validation
- **Boundaries**: Must be non-null, non-empty, and strictly sorted (increasing).
- **Stats**: Must be non-null (or created if null), same length as boundaries, and non-negative.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mLocalDate` | `java.time.LocalDate` | The date of tracking. |
| `mBucketBoundaries` | `float[]` | Lux thresholds defining the start of each bucket. |
| `mStats` | `float[]` | Time in seconds spent in each bucket. |

## API Reference
- `getLocalDate()`: Returns `LocalDate`.
- `getBucketBoundaries()`: Returns `float[]`.
- `getStats()`: Returns `float[]`.
- `log(float, float)`: (Hidden) Updates stats.

## Java-to-C++ Translation Guide

### Type Mapping
| Java | C++ Equivalent | Notes |
|------|----------------|-------|
| `LocalDate` | `std::string` (ISO-8601) or custom struct | `LocalDate` is complex. AIDL often maps it to string or a specific time structure. Here it is parcelled as a String. |
| `float[]` | `std::vector<float>` | |
| `Parcelable` | `android::os::Parcelable` | |

### Serialization
- `LocalDate` is written as a String (`dest.writeString(mLocalDate.toString())`).
- `float[]` are written using standard array write methods.

### Algorithms
- **Binary Search**: `getBucketIndex` implements a standard binary search (upper bound style) to find the range. C++ `std::upper_bound` can replace this logic.

## Test Cases
- **Constructor**:
    - `boundaries = {10, 50}`, `stats = null` -> `stats` becomes `{0, 0}`.
    - `boundaries = {50, 10}` -> Throws `IllegalArgumentException` (not sorted).
- **Logging**:
    - `boundaries = {0, 10, 100}`.
    - `log(5, 1.0)` -> index 0 (`0 <= 5 < 10`). `stats[0] += 1.0`.
    - `log(50, 2.0)` -> index 1 (`10 <= 50 < 100`). `stats[1] += 2.0`.
    - `log(200, 3.0)` -> index 2 (`100 <= 200`). `stats[2] += 3.0`.
    - `log(-1, 1.0)` -> ignored.
