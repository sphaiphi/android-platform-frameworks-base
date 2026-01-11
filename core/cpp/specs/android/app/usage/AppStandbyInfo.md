# AppStandbyInfo - Reverse Engineering Documentation

## Executive Summary
`AppStandbyInfo` is a simple data structure used to convey the "App Standby Bucket" state of a specific package across Binder IPC. It links a package name to its assigned standby bucket integer.

## Architecture Overview
This is a `final` class implementing `Parcelable`. It is effectively a struct with two fields. It is used by `UsageStatsManager` to report or set standby buckets.

## Detailed Functionality

### Core Data Encapsulation
**Purpose**: Holds a pair of (Package Name, Standby Bucket).
**Data**:
- `mPackageName`: String.
- `mStandbyBucket`: Integer (representing constants like `STANDBY_BUCKET_ACTIVE`, `STANDBY_BUCKET_RARE`, etc.).

### Parceling Logic
**Purpose**: Serialize/Deserialize.
**Algorithm**:
- **Write**: `packageName` (String), `bucket` (int).
- **Read**: `packageName` (String), `bucket` (int).

## Data Model

| Field Name | Type | Notes |
| :--- | :--- | :--- |
| `mPackageName` | `String` | Public field. |
| `mStandbyBucket` | `int` | Public field. See `UsageStatsManager` for valid values. |

## API Reference

### Constructors
- `AppStandbyInfo(String packageName, int bucket)`: Initializes fields.

### Parcelable Implementation
- `describeContents()`: Returns 0.
- `writeToParcel(Parcel dest, int flags)`: Serializes data.
- `CREATOR`: Factory for Parcel creation.

## Java-to-C++ Translation Guide

### Class Structure
- Define a struct `AppStandbyInfo`.
- `std::string` or `android::String16` for `mPackageName`.
- `int32_t` for `mStandbyBucket`.

### Constants
- The integer values for buckets are defined in `UsageStatsManager`. Ensure the C++ side has access to equivalent constants (e.g., 10 for ACTIVE, 40 for RARE).

### Serialization
- Implement `readFromParcel` and `writeToParcel`.
- Order: String, Int32.

## Test Cases & Validation
1.  **Serialization**: Create `AppStandbyInfo("com.test", 10)`. Serialize. Deserialize. Verify fields.

## Implementation Risks
- None. Very simple DTO.
