# FaceManager - Reverse Engineering Documentation

## Executive Summary
`FaceManager` is the system service manager for face authentication. It provides the public API for apps and system components to interact with face hardware. It handles authentication, enrollment, removal, challenge generation, and setting/getting features. It communicates with the `IFaceService` (System Server) via Binder.

## Architecture Overview
- **Type**: Manager / System Service Wrapper.
- **Context**: `Context.FACE_SERVICE`.
- **Communication**: Binder IPC (`IFaceService`).
- **Callback Handling**: Uses `FaceServiceReceiver` (Stub) to receive callbacks from the service and forwards them to `FaceCallback` on a provided Handler.

## Detailed Functionality

### Core Operations
- **Authenticate**: `authenticate(...)`. Prepares options, creates `FaceCallback` and `FaceServiceReceiver`, and calls `mService.authenticate`. Supports cancellation via `CancellationSignal`.
- **Detect Face**: `detectFace(...)`. Similar to authenticate but for presence detection.
- **Enroll**: `enroll(...)` / `enrollRemotely(...)`. Handles enrollment logic, checking for `hardwareAuthToken` and max templates.
- **Remove**: `remove(...)` / `removeAll(...)`. Deletes face templates.
- **Generate/Revoke Challenge**: For secure operations.
- **Set/Get Feature**: Configure face features (e.g., require attention).
- **Reset Lockout**: `resetLockout(...)`.

### Properties & State
- **Get Enrolled Faces**: `getEnrolledFaces(...)`.
- **Has Enrolled Templates**: `hasEnrolledTemplates(...)`.
- **Is Hardware Detected**: `isHardwareDetected()`.
- **Sensor Properties**: `getSensorProperties()`, `getSensorPropertiesInternal()`.

### Inner Classes
- **AuthenticationResult**: Result data for success auth.
- **AuthenticationCallback**: Client callback interface.
- **EnrollmentCallback**: Client callback interface.
- **RemovalCallback**: Client callback interface.
- **FaceServiceReceiver**: Extends `IFaceServiceReceiver.Stub`. acts as the Binder listener, forwarding events to `mFaceCallback` on the correct thread.

### Error & Help String Mapping
- `getErrorString(...)`: Maps framework `FACE_ERROR_*` constants to localized strings. Handles vendor errors.
- `getAuthHelpMessage(...)`: Maps `FACE_ACQUIRED_*` to strings for auth.
- `getEnrollHelpMessage(...)`: Maps `FACE_ACQUIRED_*` to strings for enrollment.

## Data Model
- **Service Interface**: `IFaceService`.
- **Sensors**: List of `FaceSensorPropertiesInternal`.

## Java-to-C++ Translation Guide
- **IPC**: C++ implementation would use `android::sp<IFaceService>` obtained via `ServiceManager`.
- **Callbacks**: Implement `BnFaceServiceReceiver` in C++ to receive callbacks.
- **Resource Strings**: `getErrorString` etc. rely on `Context.getString` and `R.string`. C++ code (if in a library) might not have access to Android Resources directly. If this logic is needed in C++, it usually needs a way to lookup resources or returns codes that the upper layer translates.
- **Cancellation**: `CancellationSignal` is a Java utility. C++ would likely use a mechanism to store the `requestId` (returned by auth/enroll calls in AIDL) and call `cancel...` on the service with that ID.

## Implementation Risks
- **Resource Access**: Porting string mapping logic to C++ is difficult without `Context`.
- **Permissions**: Java enforces permissions (`USE_BIOMETRIC_INTERNAL`, `MANAGE_BIOMETRIC`). C++ callers must hold these permissions (checked by System Server).

