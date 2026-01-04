# HealthStats - Reverse Engineering Documentation

## Executive Summary
`HealthStats` is an immutable container for system health metrics associated with a specific component (UID, PID, Package, Service, etc.). It acts as a strongly-typed, indexed dictionary where keys (defined in classes like `UidHealthStats`) map to specific data types: timers, measurements, or nested stats maps. It supports efficient Parceling for IPC transfer.

## Architecture Overview
-   **Pattern**: Immutable Data Object / DTO.
-   **Storage Strategy**: Arrays of primitives (`int[]`, `long[]`) and `ArrayMap`s. Data is accessed via indices derived from `HealthKeys`.
-   **Serialization**: Custom `Parcelable` implementation for efficient transport.

## Detailed Functionality

### Storage Layout
The class maintains separate arrays for each of the 5 supported metric types:
1.  **Header**: `mDataType` (String name of the source class).
2.  **Timers**: `mTimerKeys`, `mTimerCounts`, `mTimerTimes` (Single TimerStat values).
3.  **Measurements**: `mMeasurementKeys`, `mMeasurementValues` (Single Long values).
4.  **Stats**: `mStatsKeys`, `mStatsValues` (Map<String, HealthStats>).
5.  **TimersMap**: `mTimersKeys`, `mTimersValues` (Map<String, TimerStat>).
6.  **MeasurementsMap**: `mMeasurementsKeys`, `mMeasurementsValues` (Map<String, Long>).

### Access Patterns
-   **Key-based Access**: Users request data by `int key`.
-   **Index Lookup**: Uses `Arrays.binarySearch` (via `getIndex`) on the `keys` array to find the physical index in the `values` array.
-   **Immutability**: No setters. Construction happens solely via `Parcel` (reading from IPC). Note: Writing is handled by `HealthStatsWriter`, not this class.

## Data Model
-   **TimerStat**: Composite of `count` (int) and `time` (long).
-   **Measurement**: Simple `long`.
-   **Maps**: `ArrayMap` is used for string-keyed sub-metrics (e.g., specific sensor names, wake lock tags).

## API Reference
-   `hasTimer(int key)`, `getTimerCount(int key)`, `getTimerTime(int key)`: Access Timer metrics.
-   `hasMeasurement(int key)`, `getMeasurement(int key)`: Access Measurement metrics.
-   `hasStats(int key)`, `getStats(int key)`: Access nested HealthStats maps.
-   `hasTimers(int key)`, `getTimers(int key)`: Access Timer maps.
-   `hasMeasurements(int key)`, `getMeasurements(int key)`: Access Measurement maps.
-   `getDataType()`: Returns the string identifier of the stats type.

## Java-to-C++ Translation Guide

### Architecture
-   This class corresponds to a readable Data Object.
-   **C++ Equivalent**: A `struct` or `class` holding `std::vector`s or `std::map`s.
-   **Parceling**: The C++ implementation must match the `readFromParcel` logic exactly to decode data sent from Java (or vice versa).

### Data Structures
| Java | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `ArrayMap<String, T>` | `android::os::ParcelableMap` or `std::map` | `ArrayMap` is optimized for small sets; `std::map` is generic. |
| `int[] mTimerKeys` | `std::vector<int32_t>` | Keys for lookup. |
| `long[] mTimerTimes` | `std::vector<int64_t>` | Values. |

### Access Logic
-   The binary search logic for key lookup should be replicated using `std::lower_bound` on the key vector to find the index for the value vector.

## Implementation Risks
-   **Parcel Compatibility**: The serialization format is manual (writeInt, writeLong arrays). Any C++ implementation must strictly adhere to the order: Header -> TimerKeys -> TimerCounts -> TimerTimes -> MeasurementKeys -> ...
-   **Recursion**: `HealthStats` can contain nested `HealthStats` (via `mStatsValues`). Ensure the C++ Parcel reader handles this recursion correctly without stack overflow on malicious data.