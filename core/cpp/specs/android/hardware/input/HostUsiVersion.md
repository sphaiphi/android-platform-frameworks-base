# HostUsiVersion - Reverse Engineering Documentation

## Executive Summary
`HostUsiVersion` is a Parcelable data class representing the Universal Stylus Initiative (USI) version supported by the host device (screen/touch controller).

## Architecture Overview
- **Parcelable**: Implements Android's serialization mechanism.
- **Data Holder**: Immutable class holding Major and Minor version numbers.
- **Generated Code**: Uses `DataClass` annotation for boilerplate generation.

## Detailed Functionality

### Version storage
**Purpose**: Store Major and Minor version of USI.
**Data**: `int mMajorVersion`, `int mMinorVersion`.

### Validity Check
**Method**: `boolean isValid()`
**Logic**: Returns true if both major and minor versions are >= 0.

## Data Model
- `int majorVersion`
- `int minorVersion`

## API Reference
- `int getMajorVersion()`
- `int getMinorVersion()`
- `boolean isValid()`
- Parcelable methods (`writeToParcel`, `describeContents`, `CREATOR`).

## Java-to-C++ Translation Guide
- **Struct**: Simple C++ struct.
- **Serialization**: Implement corresponding `Parcel` read/write logic in C++ binder layer.
- **Types**: `int32_t`.

## Test Cases & Validation
- `isValid()` returns false for negative values.
- Serialization/Deserialization consistency.

## Implementation Risks
- None.
