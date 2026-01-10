# RemoteLockscreenValidationService - Reverse Engineering Documentation

## Executive Summary
`RemoteLockscreenValidationService` is an abstract base class for services that provide remote lockscreen validation. It allows a local device to verify a credential guess (PIN/Pattern/Password) against a remote device's lockscreen configuration.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IRemoteLockscreenValidationService.Stub` (internal wrapper).
*   **Threading**: Uses a `Handler` on the main looper to marshal binder calls to service methods.
*   **Permission**: Requires `android.permission.BIND_REMOTE_LOCKSCREEN_VALIDATION_SERVICE`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IRemoteLockscreenValidationService` binder interface.

### Core Abstract Method
*   **`onValidateLockscreenGuess(byte[] guess, OutcomeReceiver<RemoteLockscreenValidationResult, Exception> callback)`**:
    *   **Goal**: Take a binary guess (e.g., hashed PIN) and validate it.
    *   **Logic**: The implementation typically communicates with a remote device or a cloud service to perform the validation.
    *   **Result**: Success or failure is reported via the `OutcomeReceiver`, which maps back to the `IRemoteLockscreenValidationCallback`.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.remotelockscreenvalidation.RemoteLockscreenValidationService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IRemoteLockscreenValidationService.Stub`.
*   **C++**: `BnRemoteLockscreenValidationService`.

### Async Pattern
*   **Java**: Uses `OutcomeReceiver`.
*   **C++**: The AIDL uses `IRemoteLockscreenValidationCallback`. The service implementation should hold the callback and invoke `onSuccess` or `onFailure` as appropriate.

### Data Model
*   `RemoteLockscreenValidationResult` is a Parcelable that must have a C++ equivalent.

## Implementation Risks
*   **Latency**: Remote validation involves network round-trips. The UI waiting for this must handle timeouts gracefully.
*   **Security**: The `guess` byte array is extremely sensitive. It must be handled using secure memory and zeroed out after use. The transmission to the remote device must be encrypted and authenticated.
