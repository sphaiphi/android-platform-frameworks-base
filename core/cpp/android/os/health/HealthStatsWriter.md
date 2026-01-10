# HealthStatsWriter - Reverse Engineering Documentation

## Executive Summary
`HealthStatsWriter` is the mutable builder class for creating Health Stats data packets. It is optimized for low overhead, storing data in flat arrays corresponding to the indices calculated by `HealthKeys.Constants`. It provides the serialization logic (`flattenToParcel`) that `HealthStats` uses for deserialization.

## Architecture Overview
-   **Pattern**: Builder / Serializer.
-   **Dependency**: `HealthKeys.Constants` - Uses the pre-calculated indices from this class to map keys to array positions directly (O(log N) lookup happens during `Constants` initialization, but `Writer` uses pre-computed array sizes; insertion looks up index via `Constants.getIndex` which is O(log N)).
-   **Optimization**: Uses `boolean[]` fields (`mTimerFields`, `mMeasurementFields`) to track which indices have been populated, allowing sparse data population while maintaining a fixed-size internal array structure based on the schema.

## Detailed Functionality

### Initialization
-   **Constructor**: Takes `HealthKeys.Constants`. Allocates arrays (`int[]`, `long[]`, `ArrayMap[]`) based on the sizes reported by `Constants`.

### Data Population
-   **`addTimer(int timerId, ...)`**:
    1.  Resolves `timerId` to `index` using `mConstants.getIndex()`.
    2.  Sets `mTimerFields[index] = true`.
    3.  Stores values in `mTimerCounts[index]` and `mTimerTimes[index]`.
-   **`addMeasurement(int measurementId, ...)`**: Similar logic, setting `mMeasurementFields` and storing value.
-   **`addStats`, `addTimers`, `addMeasurements`**: These store nested maps (`ArrayMap`). Note that `addStats` takes a `HealthStatsWriter` as the value, enabling recursive structures.

### Serialization (`flattenToParcel`)
This is the critical serialization routine used to create the wire format for `HealthStats`.
1.  **Header**: Writes data type string.
2.  **Timers**:
    -   Writes count of set fields.
    -   Iterates keys; if `mTimerFields[i]` is true, writes Key, Count, Time.
3.  **Measurements**:
    -   Writes count of set fields.
    -   Iterates keys; if set, writes Key, Value.
4.  **Maps (Stats, Timers, Measurements)**:
    -   Writes count.
    -   Iterates keys; if map exists, writes Key then recursively calls helper to write the map content.

## Data Model
-   **Sparse Tracking**: Uses `boolean[]` markers to know which slots in the parallel arrays are valid. This avoids writing null/zero values for unset metrics to the Parcel.

## API Reference
-   `addTimer`, `addMeasurement`: Add scalar metrics.
-   `addStats`, `addTimers`, `addMeasurements`: Add map-based metrics.
-   `flattenToParcel(Parcel)`: Serializes the state.

## Java-to-C++ Translation Guide

### Architecture
-   **C++ Equivalent**: A `HealthStatsBuilder` class.
-   **Key Lookup**: Needs access to the same Key-to-Index mapping as the Java side (see `HealthKeys` analysis).

### Serialization Logic
-   The `flattenToParcel` method MUST be replicated exactly in C++ if C++ is generating these stats (e.g., in `surfaceflinger` or `system_server` native components).
-   **Order**:
    1. DataType (String)
    2. Timer Count (int) -> [Key, Count, Time] * N
    3. Measurement Count (int) -> [Key, Value] * N
    4. Stats Count (int) -> [Key, {Map Size, [String Key, Recursive Write]}] * N
    ...and so on for TimersMap and MeasurementsMap.

## Implementation Risks
-   **Index Mismatch**: If the C++ implementation uses a different set of Constants/Keys than the Java reader, the `getIndex` logic will map to the wrong array slots, or the deserializer will read garbage.
-   **Data Types**: Ensure `long` is 64-bit and `int` is 32-bit in the C++ Parcel interactions.