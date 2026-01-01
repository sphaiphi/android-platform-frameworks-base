# CameraInfo - Reverse Engineering Documentation

## Executive Summary
`CameraInfo` is a simple wrapper class that implements `Parcelable`. It is used to transport information about a camera device, such as its facing direction and orientation, between processes. It primarily composes an instance of the legacy `Camera.CameraInfo` inner class.

## Architecture Overview
This class exists primarily to overcome the limitation that nested classes cannot be directly used as top-level parcelables in some AIDL contexts. It acts as a data transfer object (DTO).

## Detailed Functionality

### Parceling
- `writeToParcel(Parcel, int)`: Writes the `facing` and `orientation` integers from the inner `Camera.CameraInfo` object to the parcel.
- `readFromParcel(Parcel)`: Reads the integers back and populates the inner object.

## Data Model
- `info`: An instance of `android.hardware.Camera.CameraInfo`.
    - `facing` (int)
    - `orientation` (int)

## API Reference
- `public Camera.CameraInfo info`
- `public void writeToParcel(Parcel out, int flags)`
- `public void readFromParcel(Parcel in)`

## Java-to-C++ Translation Guide
- **Class**: `class CameraInfo` implementing `Parcelable` -> `struct CameraInfo` or `class CameraInfo` with AIDL parcelable support.
- **Composition**: In C++, this can be a simple struct containing `facing` and `orientation` directly, or mirroring the nested structure if required for compatibility.

## Test Cases & Validation
- Verify that data written to a parcel is identical to data read from the parcel (round-trip test).

## Implementation Risks
- None, as this is a simple data holder.
