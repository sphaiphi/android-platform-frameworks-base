# UsageEventsQuery - Reverse Engineering Documentation

## Executive Summary
`UsageEventsQuery` is a DTO used to specify filter parameters when querying usage events. It allows filtering by time range, event types, and package names.

## Architecture Overview
- **Pattern**: Builder Pattern.
- **Implements**: `Parcelable`.
- **Usage**: Argument for `UsageStatsManager.queryEvents(UsageEventsQuery)`.

## Detailed Functionality

### Fields
- `mBeginTimeMillis`, `mEndTimeMillis`: Time range.
- `mEventTypes`: Array of integer event types to include. Empty means all.
- `mPackageNames`: Array of strings. Empty means all.
- `mUserId`: User ID to query for.

### Builder Validation
- Time range checks (`begin < end`).
- Null checks for arrays.

### Parceling
- Writes/Reads fields in order. Arrays are written as length + items.

## Data Model

| Field | Type | Note |
| :--- | :--- | :--- |
| `mBeginTimeMillis` | long | |
| `mEndTimeMillis` | long | |
| `mEventTypes` | int[] | |
| `mUserId` | int | |
| `mPackageNames` | String[] | |

## API Reference
- Getters return copies or Sets/Arrays.
- `Builder` class for construction.

## Java-to-C++ Translation Guide
- Simple struct with `std::vector<int32_t>` for event types and `std::vector<std::string>` for packages.
- Implement `Parcelable`.

## Test Cases & Validation
- **Serialization**: Verify arrays are correctly sized and populated.
- **Time Range**: Verify validation logic (if implementing Builder in C++).
