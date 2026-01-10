# EventStats - Reverse Engineering Documentation

## Executive Summary
`EventStats` aggregates usage statistics for a specific **Event Type** (e.g., `SCREEN_INTERACTIVE`, `KEYGUARD_SHOWN`) over a time range.

## Architecture Overview
- **Implements**: `Parcelable`.
- **Concept**: similar to `UsageStats` but focused on system events rather than package usage.

## Detailed Functionality

### Stats Tracking
- `mEventType`: The integer type of the event.
- `mBeginTimeStamp`, `mEndTimeStamp`: Range.
- `mLastEventTime`: Last occurrence.
- `mTotalTime`: Total duration (if applicable for the event type).
- `mCount`: Number of occurrences.

### Merge Logic (`add`)
**Purpose**: Combine two `EventStats` objects of the same type.
**Algorithm**:
1.  Verify `mEventType` matches.
2.  Update `mLastEventTime`: Max of both.
3.  Update `mBeginTimeStamp`: Min of both.
4.  Update `mEndTimeStamp`: Max of both.
5.  Accumulate `mTotalTime` + right.mTotalTime.
6.  Accumulate `mCount` + right.mCount.

### Parceling
- Standard write/read of fields.

## Data Model

| Field | Type | Note |
| :--- | :--- | :--- |
| `mEventType` | int | |
| `mBeginTimeStamp` | long | |
| `mEndTimeStamp` | long | |
| `mLastEventTime` | long | |
| `mTotalTime` | long | |
| `mCount` | int | |

## API Reference
- Getters for all fields.
- `add(EventStats right)`: Merges data.

## Java-to-C++ Translation Guide
- Struct with `int32_t` and `int64_t`.
- Logic is straightforward arithmetic.

## Test Cases & Validation
1.  **Merge**: Create two stats for `SCREEN_INTERACTIVE`.
    - A: Range [0, 100], Count 5, Total 50.
    - B: Range [100, 200], Count 3, Total 30.
    - Result: Range [0, 200], Count 8, Total 80.
