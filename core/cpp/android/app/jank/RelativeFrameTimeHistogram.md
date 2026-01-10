# RelativeFrameTimeHistogram - Reverse Engineering Documentation

## Executive Summary
`RelativeFrameTimeHistogram` is a utility class that models the distribution of frame rendering times relative to the frame deadline. It maintains a set of counters corresponding to predefined time buckets (e.g., "-20ms", "0ms", "+10ms"). This allows granular analysis of how early or late frames are being presented.

## Architecture Overview
- **Type**: Data Structure / Helper.
- **Dependencies**: None (Pure logic).
- **Internal State**:
    - `mBucketCounts`: Integer array of counters.
    - `sBucketEndpoints`: Static definition of bucket ranges.

## Detailed Functionality

### 1. Bucketing Logic
**Concept**: The histogram uses non-linear buckets to provide higher resolution near the deadline (0ms).
**Endpoints**: Defined in `sBucketEndpoints`. Range from `Integer.MIN_VALUE` to `Integer.MAX_VALUE`.
**Mapping**:
- Negative values: Frame was early (e.g., -5ms means 5ms headroom).
- Zero: On time.
- Positive values: Frame was late (Jank).

### 2. Adding Data
**Method**: `addRelativeFrameTimeMillis(int frameTimeMillis)`
- Calls `getRelativeFrameTimeBucketIndex` to find the correct index.
- Increments `mBucketCounts[index]`.

### 3. Index Calculation
**Method**: `getRelativeFrameTimeBucketIndex(int relativeFrameTime)`
**Algorithm**:
- A manual decision tree (series of `if` statements) is used to map the continuous integer time to a discrete bucket index.
- This effectively acts as a hardcoded binary search or interval tree optimization.
- **Logic**:
    - `< 20`: Checks ranges like [-200, -100], [-30, -20], etc.
    - `< 30`: Maps to indices around 32.
    - ... and so on up to 1000ms.

## Data Model

### Fields
- `mBucketCounts`: `int[]`. Size is `sBucketEndpoints.length - 1`.
- `sBucketEndpoints`: `static final int[]`. Size 53.

## API Reference

### Public Methods
- `addRelativeFrameTimeMillis(int)`: Update histogram.
- `getBucketCounters()`: Returns copy of counters array.
- `getBucketEndpointsMillis()`: Returns copy of endpoints array.

## Java-to-C++ Translation Guide

### Hardcoded Logic
The `getRelativeFrameTimeBucketIndex` method contains "magic numbers" (e.g., offsets like `+12`, `+32`).
- **C++**: Copy the logic exactly to ensure the histogram bins match the Java side 1:1. Any deviation will cause stats mismatch.
- **Optimization**: Since `sBucketEndpoints` is constant, `std::upper_bound` could be used, but the manual if/else chain is likely faster for the specific distribution expected.

### Arrays
- **Java**: `int[]`.
- **C++**: `std::vector<int>` or `std::array<int, N>` if N is fixed. Since the size is fixed at compile time (based on endpoints), `std::array` is preferred.

## Test Cases & Validation
- **Input**: -25
- **Expected Bucket**: The one corresponding to range [-30, -25).
- **Input**: 0
- **Expected Bucket**: The one corresponding to [0, 2).

## Implementation Risks
- **Index Out of Bounds**: The logic seems robust, covering `MIN_VALUE` to `MAX_VALUE`, but C++ array access should ideally be checked or proven safe.
