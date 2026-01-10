# CameraStatus - Reverse Engineering Documentation

## Executive Summary
`CameraStatus` is a hidden (`@hide`) parcelable class that provides information about the current status of a camera device. This includes whether it is available, who is using it, and which physical cameras (in a multi-camera setup) are currently unavailable.

## Architecture Overview
It is a simple data transport class used by the `ICameraServiceListener` to notify clients about changes in the camera system's state.

## Detailed Functionality

### Data Fields
- `cameraId`: The unique identifier for the camera.
- `status`: An integer representing the current state (mapping to `ICameraServiceListener.STATUS_*`).
- `unavailablePhysicalCameras`: An array of strings identifying physical cameras that cannot be used.
- `clientPackage`: The package name of the application currently using the camera (if any).
- `deviceId`: The ID of the device associated with this camera.

## Data Model
- **Status**: Typical values include `STATUS_PRESENT`, `STATUS_NOT_PRESENT`, `STATUS_ENUMERATING`, `STATUS_OCCUPIED`, `STATUS_NOT_AVAILABLE`.

## API Reference
- `public String cameraId`
- `public int status`
- `public String[] unavailablePhysicalCameras`
- `public String clientPackage`
- `public int deviceId`

## Java-to-C++ Translation Guide
- **Class**: `class CameraStatus` -> `struct CameraStatus`.
- **Arrays**: `String[]` -> `std::vector<std::string>`.
- **Parceling**: Standard `Parcel` read/write operations.

## Implementation Risks
- Synchronization of status constants between Java, C++, and AIDL definitions.
