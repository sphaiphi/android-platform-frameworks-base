# JankDataProcessor - Reverse Engineering Documentation

## Executive Summary
`JankDataProcessor` is the core logic engine for processing raw frame data received from SurfaceFlinger. It associates these frames with high-level widget states (managed by `StateTracker`) to attribute jank to specific UI elements. It aggregates these statistics in memory and periodically flushes them to the system logging daemon (`FrameworkStatsLog`).

## Architecture Overview
- **Dependencies**:
    - `StateTracker`: Source of truth for active widget states during specific time windows.
    - `PendingJankStat`: (Inner class) Mutable accumulator for stats.
    - `SimplePool`: Object pooling for memory optimization.
- **Threading**: Designed to be called from the `JankTracker` background thread. Not inherently thread-safe itself; relies on external serialization (via the handler thread).

## Detailed Functionality

### 1. processing Jank Data
**Method**: `processJankData(List<JankData> jankData, String activityName, int appUid)`
**Algorithm**:
1.  **Retrieve States**: Fetch all active and previously active states from `StateTracker` into `mPendingStates`.
2.  **Correlate Frames**: Iterate through each frame in `jankData`:
    - Iterate through `mPendingStates`.
    - **Match Condition**: If `frame.vsyncId` is within `[state.vsyncIdStart, state.vsyncIdEnd]`:
        - Call `recordFrameCount` to update stats.
        - Mark state as processed (`pendingState.mProcessed = true`).
3.  **Log**: Call `incrementBatchCountAndMaybeLogStats()` to check if a flush is needed.
4.  **Cleanup**: Call `jankDataProcessingComplete()` to return state objects to their pool.

### 2. Aggregation Logic
**Method**: `recordFrameCount`
- **Lookup**: specific pending stat using `stateData.mStateDataKey`.
- **Creation**: If not found, acquire from `mPendingJankStatsPool` (or create new).
- **Update**:
    - Increment `mTotalFrames`.
    - If `frame.jankType` has `JANK_APPLICATION`, increment `mJankyFrames`.
    - Update histogram via `recordFrameOverrun` using `frame.actualAppFrameTimeNanos`.
    - Update `processedVsyncId` to avoid double counting.

### 3. Merging External Stats
**Method**: `mergeJankStats`
- Allows merging fully formed `AppJankStats` (from external components) into the current pending aggregation.
- Merges histograms by summing bucket counters.

### 4. Logging & flushing
**Method**: `logMetricCounts`
- Triggered when `mCurrentBatchCount >= LOG_BATCH_FREQUENCY` (50).
- Iterates over `mPendingJankStats`.
- Writes to `FrameworkStatsLog`.
- Returns `PendingJankStat` objects to the pool.
- Clears `mPendingJankStats` map.

## Data Model

### Inner Class: PendingJankStat
Mutable accumulator for statistics.
- **Fields**: `uid`, `activityName`, `widgetId`, `category`, `state`, `totalFrames`, `jankyFrames`, `processedVsyncId`, `mFrameOverrunBuckets` (int array).
- **Histogram Logic**: Contains specific logic to map frame overrun time (ms) to bucket indices. See `sFrameOverrunHistogramBounds`.

## Java-Specific Features

### 1. Object Pooling (`SimplePool`)
**Usage**: `StateData` and `PendingJankStat` objects are pooled to reduce garbage collection pressure given the high frequency of frame events.
**C++ Translation**:
- Use `std::vector` with `reserve()` or a custom slab allocator if heap fragmentation is a concern.
- Since C++ allows stack allocation and value semantics, extensive pooling might be less critical than in Java, but reusing objects in a vector is still good practice for cache locality.

### 2. HashMap Usage
**Usage**: `mPendingJankStats` uses a `String` key (concatenation of category + ID + state).
**C++ Translation**:
- `std::unordered_map` or `std::map`.
- Constructing the string key (`category + id + state`) for every lookup is expensive. C++ should consider a composite key struct with a custom hash function to avoid string allocations.

## API Reference

### Public Methods
- `processJankData(...)`: Main entry point for SurfaceFlinger callbacks.
- `mergeJankStats(...)`: API for manual stat injection.
- `logMetricCounts()`: Forces a flush of logs.

## Java-to-C++ Translation Guide

### Histogram Bucket Logic
The `indexForFrameOverrun` method contains a hardcoded decision tree for bucket mapping.
- **C++**: This can be implemented exactly as is, or optimized using `std::upper_bound` on a static `constexpr` array of thresholds if the branch prediction overhead is high, though the current if/else chain is likely quite fast.

### FrameworkStatsLog
- **Context**: This is an auto-generated Android internal class.
- **C++ Equivalent**: Use the native StatsD client (`stats_event` APIs) to write to the same atoms.

## Edge Cases
- **Overrun Calculation**: `frameTimeNano / NANOS_PER_MS` (integer division). Precision loss is intentional.
- **Pool Exhaustion**: If `mPendingJankStats` exceeds `MAX_IN_MEMORY_STATS` (25), new stats are dropped/ignored to prevent memory leaks.

## Implementation Risks
- **Batching & Memory**: The logic relies on periodic flushing. If `processJankData` stops being called, stats might sit in memory indefinitely.
- **Key Collisions**: The String key is simple concatenation. Theoretically, "A" + "B" collision with "AB" + "". Ensure delimiters are used or structure the key safely in C++.
