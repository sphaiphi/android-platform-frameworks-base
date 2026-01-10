# RotationResolverService - Reverse Engineering Documentation

## Executive Summary
`RotationResolverService` is a system service base class used to provide intelligent screen rotation recommendations. It is primarily used to implement "Face-based Auto-rotate," where the device uses the front-facing camera to determine the orientation of the user's face relative to the device, ensuring the screen rotates only when the user's perspective changes.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IRotationResolverService.Stub`.
*   **Threading**: Uses a `Handler` on the main looper to marshal binder calls to the service implementation.
*   **Permission**: Requires `android.permission.BIND_ROTATION_RESOLVER_SERVICE`.
*   **Request Management**: Enforces a singleton request model. Only one rotation resolution request can be active at a time. New requests will be rejected with `ROTATION_RESULT_FAILURE_PREEMPTED` if a current valid request is still processing.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IRotationResolverService` binder interface.

### Core Abstract Method
*   **`onResolveRotation(RotationResolutionRequest, CancellationSignal, RotationResolverCallback)`**:
    *   **Goal**: Determine the desired screen rotation.
    *   **Parameters**:
        *   `RotationResolutionRequest`: Contains the current rotation and a timeout.
        *   `CancellationSignal`: Allows the system to cancel the request (e.g., if the user turns off the screen).
        *   `RotationResolverCallback`: Used to return the result (`onSuccess`) or an error (`onFailure`).
    *   **Logic**: The implementation typically uses camera data or sensor fusion to decide the best rotation.

### Result Handling
*   **Success**: Returns one of `Surface.ROTATION_0`, `90`, `180`, or `270`.
*   **Failure**: Returns a failure code:
    *   `CANCELLED`: System no longer needs the result.
    *   `TIMED_OUT`: Service took too long.
    *   `PREEMPTED`: A newer request arrived.
    *   `NOT_SUPPORTED`: Service cannot perform the check currently (e.g., camera in use).

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.rotationresolver.RotationResolverService"`

### Inner Interface
*   `RotationResolverCallback`: The client-facing interface for returning results.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IRotationResolverService.Stub`.
*   **C++**: `BnRotationResolverService`.

### Data Model
*   `RotationResolutionRequest` is a Parcelable.
*   The rotation values are standard `android::view::Rotation` (or int constants).

### Dependencies
*   Implementations often depend on `Camera` or `Face` detection HALs. In C++, this involves using `ACameraManager` or binder links to `IVirtualCamera` / `IFace`.

## Implementation Risks
*   **Latency**: The decision must be made quickly (well under 1 second) to feel responsive to the user.
*   **Privacy**: Using the camera for rotation detection is sensitive. The service must ensure that camera data is processed locally and no images are stored or transmitted.
*   **Power Consumption**: Using the camera/NPU frequently for rotation can drain the battery. The system (via `RotationResolverManagerService`) throttles these requests.
