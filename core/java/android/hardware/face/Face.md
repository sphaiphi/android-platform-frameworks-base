# Face - Reverse Engineering Documentation

## Executive Summary
`Face` is a data class representing a face biometric identifier. It extends `BiometricAuthenticator.Identifier`, inheriting common biometric identifier properties like name, ID, and device ID. It is Parcelable, allowing it to be passed across process boundaries.

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.BiometricAuthenticator.Identifier`.
- **Implements**: `android.os.Parcelable`.
- **Purpose**: Represents a single enrolled face template.

## Detailed Functionality

### Constructors
- `Face(CharSequence name, int faceId, long deviceId)`: Public constructor to create a `Face` object with a name, a unique face ID (biometric ID), and the device ID it belongs to.
- `Face(Parcel in)`: Private constructor used by `CREATOR` to reconstruct the object from a Parcel.

### Parcelable Implementation
- `describeContents()`: Returns 0.
- `writeToParcel(Parcel out, int flags)`: Writes the name, biometric ID, and device ID to the parcel.
- `CREATOR`: Standard `Parcelable.Creator` implementation.

## Data Model
- **Name**: `CharSequence` (from superclass) - A user-friendly name for the face.
- **Biometric ID**: `int` (from superclass) - A unique identifier for the face template.
- **Device ID**: `long` (from superclass) - The identifier of the device where the face is enrolled.

## API Reference
- `Face(CharSequence name, int faceId, long deviceId)`
- `writeToParcel(Parcel out, int flags)`
- `describeContents()`

## Java-to-C++ Translation Guide
- **Class**: Map to a C++ struct or class, e.g., `Face`.
- **Inheritance**: Can inherit from a C++ equivalent of `BiometricAuthenticator.Identifier` if it exists, or just contain the fields directly.
- **Parcelable**: Implement `android::os::Parcelable` interface in C++.
- **Fields**:
    - `CharSequence name` -> `android::String16` or `std::string`
    - `int faceId` -> `int32_t`
    - `long deviceId` -> `int64_t`

## Test Cases & Validation
- **Serialization**: Verify that a `Face` object written to a Parcel in Java can be correctly read in C++ (and vice-versa if needed).
- **Equality**: Check if two `Face` objects with same ID and Device ID are treated as equal (logic usually in superclass).
