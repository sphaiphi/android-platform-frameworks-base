# UsageStatsManager - Reverse Engineering Documentation

## Executive Summary
`UsageStatsManager` is the primary system service wrapper for accessing usage statistics. It defines constants for intervals and buckets, and provides methods to query stats, events, and manage app standby buckets.

## Architecture Overview
- **Service**: `Context.USAGE_STATS_SERVICE`.
- **IPC**: Wraps `IUsageStatsManager`.
- **Constants**: Defines `INTERVAL_*`, `STANDBY_BUCKET_*`, `REASON_*`.

## Detailed Functionality

### Constants
- **Intervals**: DAILY, WEEKLY, MONTHLY, YEARLY, BEST.
- **Buckets**: ACTIVE (10), WORKING_SET (20), FREQUENT (30), RARE (40), RESTRICTED (45), EXEMPTED (5), NEVER (50).
- **Reasons**: Bitmasks for why a bucket was assigned (Main reason | Sub reason).

### Query Methods
- `queryUsageStats`: Returns list of `UsageStats`.
- `queryEvents`: Returns `UsageEvents` iterator.
- `queryEventStats`: Returns `EventStats`.
- `queryBroadcastResponseStats`.

### Management Methods
- `setAppStandbyBucket`: Manually set a bucket (requires permission).
- `getAppStandbyBucket`: Get current bucket.
- `registerAppUsageObserver`: Register for time limit callbacks.

## Data Model
- Mostly constants and wrapper calls.

## Java-to-C++ Translation Guide
- **Constants**: Map these 1:1 to C++ constants/enums.
- **Bitwise Operations**: `reasonToString` logic parses the high/low bits of the reason code. Replicate this utility if needed.

## Implementation Risks
- **Permission Handling**: While the wrapper assumes permissions are checked by the service, any client-side logic relying on permissions (like `UserHandleAware`) is implicit.

## Questions for C++ Team
- Do we need to implement the Observer registration logic in C++? This involves `PendingIntent`, which is a complex Android object to handle in native code.
