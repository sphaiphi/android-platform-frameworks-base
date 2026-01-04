# RotationResolverInternal - Reverse Engineering Documentation

## Executive Summary
`RotationResolverInternal` is an abstract internal service interface within the Android framework. It serves as the bridge between the system server (specifically the window manager or display rotation logic) and the `RotationResolverService`. Its primary purpose is to allow the system to intelligently determine the correct screen orientation based on various sensor data (like camera-based face detection) when the standard sensor-based orientation might be ambiguous or inaccurate.

## Architecture Overview
The component follows a standard Android internal service pattern:
- **Internal API**: Marked with `@hide`, indicating it is not part of the public SDK and is intended for use by other system components.
- **Asynchronous Pattern**: Uses a callback mechanism (`RotationResolverCallbackInternal`) and a `CancellationSignal` to handle potentially long-running sensor-based calculations without blocking the caller.
- **Abstraction**: Defined as an `abstract class` to allow the actual implementation (likely handled by a concrete manager class) to be swapped or mocked during testing.

## Detailed Functionality

### `isRotationResolverSupported()`
**Purpose**: Checks if the rotation resolution feature is available on the current device hardware/software configuration.
**C++ Implementation Guidance**: This should be a simple boolean check, possibly querying a system property or a feature flag.

### `resolveRotation(...)`
**Purpose**: Requests a refined screen rotation calculation.
**Parameters**:
- `callback`: An internal callback interface to receive success or failure notifications.
- `packageName`: String identifying the foreground application, likely for logging or permission/attribution purposes.
- `proposedRotation`: The rotation the system *thinks* should be applied (based on standard accelerometers).
- `currentRotation`: The rotation currently active on the device.
- `timeoutMillis`: A timeout value. If resolution exceeds this, a failure is reported.
- `cancellationSignal`: Allows the caller to abort the request if the rotation is no longer needed.
**Algorithm**:
1. Validates input parameters.
2. Forwards the request to the bound `RotationResolverService`.
3. Monitors the `cancellationSignal` to stop processing if requested.
4. Enforces the `timeoutMillis` timer.
5. Invokes the appropriate callback method based on the service result.

## Data Model

### Screen Rotation Constants
These are integers defined in `android.view.Surface`:
- `ROTATION_0`: 0
- `ROTATION_90`: 1
- `ROTATION_180`: 2
- `ROTATION_270`: 3

### Failure Codes
Integers defined in `android.service.rotationresolver.RotationResolverService`:
- `ROTATION_RESULT_FAILURE_NOT_SUPPORTED`
- `ROTATION_RESULT_FAILURE_TIMED_OUT`
- `ROTATION_RESULT_FAILURE_PREEMPTED`
- `ROTATION_RESULT_FAILURE_CANCELLED`
- `ROTATION_RESULT_FAILURE_UNKNOWN`

## API Reference

### `RotationResolverInternal` (Abstract Class)
| Method | Return Type | Description |
| :--- | :--- | :--- |
| `isRotationResolverSupported()` | `boolean` | Returns true if the service is available. |
| `resolveRotation(...)` | `void` | Initiates an asynchronous rotation query. |

### `RotationResolverCallbackInternal` (Interface)
| Method | Parameters | Description |
| :--- | :--- | :--- |
| `onSuccess` | `@Surface.Rotation int result` | Called when a rotation is successfully resolved. |
| `onFailure` | `@FailureCodes int error` | Called when the resolution process fails. |

## Java-to-C++ Translation Guide

### Component Mapping
- **Abstract Class**: Use a C++ abstract base class with `virtual` methods and a `virtual` destructor.
- **Callback Interface**: Use a C++ abstract class or a struct of `std::function` objects.
- **Surface.Rotation**: Use a scoped `enum class Rotation : int32_t`.
- **CancellationSignal**: Use a thread-safe cancellation token mechanism (e.g., `std::stop_token` from C++20).
- **DurationMillisLong**: Use `std::chrono::milliseconds`.

### Memory Management
In Java, the callback and signal are garbage collected. In C++, ownership must be explicitly defined:
- The `RotationResolverInternal` implementation should likely not own the callback, or it should use a `std::weak_ptr` if the lifecycle is uncertain.
- Ensure that if the caller is destroyed, the callback is not invoked (or the implementation handles the dangling reference).

## Implementation Risks
- **Race Conditions**: Since rotation resolution is asynchronous and can be cancelled, ensure that the callback is not invoked after `onFailure` or after the `CancellationSignal` has been triggered.
- **Timeout Precision**: Ensure the C++ timer implementation is consistent with the system's clock expectations.
- **AIDL Integration**: This internal class likely interacts with an AIDL-defined service. The C++ implementation must correctly handle the Binder death recipients and proxy calls.
