# AppLaunchEstimateInfo - Reverse Engineering Documentation

## Executive Summary
`AppLaunchEstimateInfo` is a simple data transfer object (DTO) used to transport an estimated launch time for a specific application package. It is designed to be passed across processes via Binder IPC.

## Architecture Overview
This class is a `final` class implementing the `Parcelable` interface. It serves as a container for two pieces of immutable data: a package name and a timestamp. It has no dependencies other than standard Android IPC primitives.

## Detailed Functionality

### Core Data Encapsulation
**Purpose**: Stores the estimated launch time for a package.
**Data**:
- `packageName`: String identifying the application.
- `estimatedLaunchTime`: Long representing the estimated launch time in milliseconds (system time).

### Parceling Logic
**Purpose**: Serialize/Deserialize data for IPC.
**Algorithm**:
1.  **Write**: Write `packageName` (String), then `estimatedLaunchTime` (long) to the Parcel.
2.  **Read**: Read `packageName` (String), then `estimatedLaunchTime` (long) from the Parcel.

## Data Model

| Field Name | Type | Notes |
| :--- | :--- | :--- |
| `packageName` | `String` | The package identifier. Immutable public field. |
| `estimatedLaunchTime` | `long` | Timestamp (milliseconds). Immutable public field. |

## API Reference

### Constructors
- `AppLaunchEstimateInfo(String packageName, long estimatedLaunchTime)`: Public constructor to initialize the fields.

### Parcelable Implementation
- `describeContents()`: Returns 0.
- `writeToParcel(Parcel dest, int flags)`: Flattens the object into the parcel.
- `CREATOR`: Static field for creating instances from a Parcel.

## Java-to-C++ Translation Guide

### Class Structure
- Define a struct or class (e.g., `AppLaunchEstimateInfo`) in the appropriate namespace (e.g., `android::app::usage`).
- Member variables should be `std::string` for package name and `int64_t` for the timestamp.

### Serialization
- Implement `android::Parcelable` interface in C++.
- Use `Parcel::writeString16` (or `writeString8` if strictly ASCII/UTF-8, but Java `writeString` usually implies UTF-16 in Binder context unless `readString8` was used, here it is `readString`/`writeString` which corresponds to `writeString16` in C++ usually, though modern Android often uses UTF-8). *Correction*: Java `Parcel.writeString` writes UTF-16. C++ `Parcel::writeString16` should be used, or `Parcel::writeString` which handles string types.
- **Note**: Ensure the read/write order matches exactly: String then Long.

### Memory Management
- The Java class is immutable. The C++ implementation should ideally also be immutable or value-type semantic.

## Test Cases & Validation
1.  **Round Trip**: Write an `AppLaunchEstimateInfo` to a Parcel in Java, read it in C++ (and vice-versa).
    - Input: `packageName="com.example.app"`, `estimatedLaunchTime=123456789`
    - Verify: Retrieved object has identical values.
2.  **Null Handling**: Check if `packageName` can be null. The Java code has `@NonNull` on the class usually but this file doesn't explicitly check in constructor (it just assigns). However, `Parcel.writeString` handles null.

## Questions for C++ Team
- Should the C++ class use `android::String16` or `std::string` (UTF-8) for `packageName`? (Standard Binder usually uses String16).
