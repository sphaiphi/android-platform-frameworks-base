# UsageStats - Reverse Engineering Documentation

## Executive Summary
`UsageStats` aggregates usage data for a single package over a time interval. It tracks foreground time, visibility time, launch counts, and last-used timestamps.

## Architecture Overview
- **Implements**: `Parcelable`.
- **Core Logic**: Aggregation via `add()` and `update()`.

## Detailed Functionality

### Fields
- **Identity**: `mPackageName`.
- **Time Range**: `mBeginTimeStamp`, `mEndTimeStamp`.
- **Usage Metrics**:
    - `mTotalTimeInForeground`: Total time resumed.
    - `mTotalTimeVisible`: Total time visible (resumed + paused).
    - `mTotalTimeForegroundServiceUsed`.
    - `mLastTimeUsed`, `mLastTimeVisible`, `mLastTimeForegroundServiceUsed`, `mLastTimeComponentUsed`.
    - `mLaunchCount`, `mAppLaunchCount`.
- **State Tracking**:
    - `mActivities` (SparseIntArray): Maps Activity Instance ID -> Last Event (Resumed/Paused).
    - `mForegroundServices` (ArrayMap): Maps Class Name -> Last Event.
    - `mChooserCounts`: Usage of share sheet targets.

### Aggregation Logic (`add`)
**Purpose**: Merge two stats objects (e.g., daily stats into weekly stats).
**Algorithm**:
1.  Verify package name match.
2.  Update timestamps (expand range).
3.  Sum durations and counts.
4.  **Merge Maps**: `mActivities`, `mForegroundServices`, `mChooserCounts` are merged. Max event types are kept for state maps; counts are summed for chooser counts.
5.  Max `mLastTime...` fields.

### Update Logic (`update`)
**Purpose**: Update stats based on a single new `UsageEvents.Event`.
**Algorithm**:
- **Activity Events**: Update `mActivities` map. Calculate time deltas if event is PAUSED/STOPPED (time since RESUMED).
- **Service Events**: Update `mForegroundServices`. Calculate time deltas.
- **Timestamps**: Update `mLastTime...` based on event type.

## Data Model
- See fields above. Note usage of `SparseIntArray` and `ArrayMap` which are Android specific optimized collections.

## API Reference
- Getters for all metrics.
- `add(UsageStats)`: Merge.
- `update(...)`: Process event.

## Java-to-C++ Translation Guide
- **Collections**:
    - `SparseIntArray` -> `std::map<int, int>` or `std::unordered_map`.
    - `ArrayMap` -> `std::map` or `std::unordered_map`.
- **Logic**: The `add` and `update` logic is stateful and complex. It requires precise replication of the state machine (e.g., calculating duration only when transitioning from RESUMED to PAUSED).

## Implementation Risks
- **State Machine Parity**: Calculating `mTotalTimeInForeground` correctly depends on tracking the state of activities accurately. Any deviation in the logic will result in incorrect stats.
