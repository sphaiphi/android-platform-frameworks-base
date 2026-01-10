# BroadcastResponseStats - Reverse Engineering Documentation

## Executive Summary
`BroadcastResponseStats` aggregates statistics regarding how an application responds to broadcasts. It tracks metrics like broadcasts dispatched, notifications posted/updated/cancelled in response to a broadcast.

## Architecture Overview
This is an immutable `Parcelable` class. It is used to query statistics via `UsageStatsManager`. It maintains a package name, a broadcast ID, and several integer counters.

## Detailed Functionality

### Stats Accumulation
**Purpose**: Track response actions.
**Fields**:
- `mPackageName`: Target package.
- `mId`: ID of the broadcast (set via `BroadcastOptions`).
- `mBroadcastsDispatchedCount`: Number of broadcasts sent.
- `mNotificationsPostedCount`: Notifications posted shortly after broadcast.
- `mNotificationsUpdatedCount`: Notifications updated.
- `mNotificationsCancelledCount`: Notifications cancelled.

**Operations**:
- **Incrementers**: Methods like `incrementBroadcastsDispatchedCount(int count)` add to the internal counters.
- **Aggregation**: `addCounts(BroadcastResponseStats stats)` merges another stats object into this one by summing the counters.

### Parceling Logic
**Algorithm**:
- **Write**: `mPackageName` (String8), `mId` (long), then 4 `int`s (dispatched, posted, updated, cancelled).
- **Read**: Matches write order.
- **Note**: Uses `readString8`/`writeString8`, which suggests an optimization for UTF-8 or ASCII package names.

## Data Model

| Field Name | Type | Notes |
| :--- | :--- | :--- |
| `mPackageName` | `String` | Immutable. |
| `mId` | `long` | Immutable. ID > 0. |
| `mBroadcastsDispatchedCount` | `int` | Mutable via incrementers. |
| `mNotificationsPostedCount` | `int` | Mutable via incrementers. |
| `mNotificationsUpdatedCount` | `int` | Mutable via incrementers. |
| `mNotificationsCancelledCount` | `int` | Mutable via incrementers. |

## API Reference

- `getPackageName()`, `getId()`: Getters for identity.
- `get*Count()`: Getters for stats.
- `increment*Count(int)`: Internal mutators (hidden).
- `addCounts(BroadcastResponseStats)`: Aggregation logic.
- `equals()`, `hashCode()`: Implemented based on all fields.

## Java-to-C++ Translation Guide

### Type Mapping
- `mId` -> `int64_t`.
- Counts -> `int32_t`.
- `mPackageName` -> `std::string` (since `writeString8` is used).

### Serialization
- Use `Parcel::writeString8` and `Parcel::readString8` if available in the specific NDK/platform version C++ wrapper, otherwise standard string writing but ensure encoding compatibility. *Correction*: In native Parcel, `writeString8` exists.
- Order: String8, Long, Int, Int, Int, Int.

### Equality
- Implement `operator==` checking all fields.

## Test Cases & Validation
1.  **Aggregation**: Create two objects for same package/ID with different counts. Call `addCounts`. Verify sums.
2.  **Parceling**: Verify that `writeString8` is correctly handled.

## Implementation Risks
- **String Encoding**: Explicit use of `readString8` in Java suggests specific encoding expectations (UTF-8). C++ Parcel implementation must match this.
