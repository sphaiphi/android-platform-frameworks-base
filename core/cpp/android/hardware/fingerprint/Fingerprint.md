# Fingerprint - Reverse Engineering Documentation

## Executive Summary
`Fingerprint` is a data class representing a fingerprint biometric identifier. It extends `BiometricAuthenticator.Identifier` and adds a group ID to associate fingerprints with specific groups (usually corresponding to a user ID). It is Parcelable, allowing it to be passed across process boundaries.

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.BiometricAuthenticator.Identifier`.
- **Implements**: `android.os.Parcelable`.
- **Purpose**: Represents a single enrolled fingerprint template.

## Detailed Functionality

### Constructors
- `Fingerprint(CharSequence name, int groupId, int fingerId, long deviceId)`: Public constructor to create a `Fingerprint` object with a name, group ID, unique finger ID (biometric ID), and device ID.
- `Fingerprint(CharSequence name, int fingerId, long deviceId)`: Constructor without group ID.
- `Fingerprint(Parcel in)`: Private constructor used by `CREATOR` to reconstruct the object from a Parcel.

### Parcelable Implementation
- `describeContents()`: Returns 0.
- `writeToParcel(Parcel out, int flags)`: Writes the name, biometric ID, device ID, and group ID to the parcel.
- `CREATOR`: Standard `Parcelable.Creator` implementation.

## Data Model
- **Name**: `CharSequence` (from superclass) - A user-friendly name for the fingerprint.
- **Biometric ID**: `int` (from superclass) - A unique identifier for the fingerprint template.
- **Device ID**: `long` (from superclass) - The identifier of the device where the fingerprint is enrolled.
- **Group ID**: `int` - An identifier for the group this fingerprint belongs to (often the user ID).

## API Reference
- `getGroupId()`: Returns the group ID.
- `writeToParcel(Parcel out, int flags)`
- `describeContents()`

## Java-to-C++ Translation Guide
- **Class**: Map to a C++ struct or class, e.g., `Fingerprint`.
- **Inheritance**: Can inherit from a C++ equivalent of `BiometricAuthenticator.Identifier` if it exists, or just contain the fields directly.
- **Parcelable**: Implement `android::os::Parcelable` interface in C++.
- **Fields**:
    - `CharSequence name` -> `android::String16` or `std::string`
    - `int fingerId` -> `int32_t`
    - `long deviceId` -> `int64_t`
    - `int groupId` -> `int32_t`

## Test Cases & Validation
- **Serialization**: Verify that a `Fingerprint` object written to a Parcel in Java can be correctly read in C++ (and vice-versa if needed).
