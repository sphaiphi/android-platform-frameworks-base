# CacheQuotaHint - Reverse Engineering Documentation

## Executive Summary
`CacheQuotaHint` represents a suggestion or request for cache quota allocation. It encapsulates a Volume UUID, a UID, UsageStats, and a quota value. It acts as a request object sent to `CacheQuotaService`.

## Architecture Overview
- **Pattern**: Builder Pattern (`CacheQuotaHint.Builder`) used for construction.
- **Implements**: `Parcelable`.
- **Usage**: Used in the `CacheQuotaService` API to assist the system in deciding how much cache space to allot to an app.

## Detailed Functionality

### Fields
- `mUuid` (String): Volume UUID.
- `mUid` (int): User ID + App ID.
- `mUsageStats` (UsageStats): Usage statistics associated with the request (can be null).
- `mQuota` (long): The calculated or requested quota in bytes. Default is `QUOTA_NOT_SET` (-1).

### Validation
- `mUid` must be non-negative.
- `mQuota` must be >= `QUOTA_NOT_SET`.

### Parceling
- Writes/Reads fields in order: UUID, UID, Quota, UsageStats (Parcelable).

## Data Model

| Field | Type | Note |
| :--- | :--- | :--- |
| `mUuid` | String | Nullable. |
| `mUid` | int | |
| `mUsageStats` | UsageStats | Nullable. Parcelable. |
| `mQuota` | long | |

## API Reference
- `getVolumeUuid()`, `getUid()`, `getQuota()`, `getUsageStats()`.
- `equals()` / `hashCode()` based on all fields.

## Java-to-C++ Translation Guide

### Class Structure
- Class with getters and a Builder (inner class) to match the Java design pattern.

### Serialization
- UUID is a String (likely UTF-16 in standard parceling, check `writeString` usage).
- `UsageStats` is a nested Parcelable. The C++ code needs to handle the case where `mUsageStats` is null (Java uses `writeParcelable` which handles nulls).

## Test Cases & Validation
1.  **Builder**: Verify Builder enforces non-negative UID.
2.  **Parceling**: Test with and without `UsageStats` to ensure null handling works.
