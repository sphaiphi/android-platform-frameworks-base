# FingerprintManager - Reverse Engineering Documentation

## Executive Summary
`FingerprintManager` is the system service manager for fingerprint authentication. It provides the public API for interacting with fingerprint hardware (Authenticate, Enroll, Remove, Detect, etc.). It communicates with `IFingerprintService` via Binder.

## Architecture Overview
- **Type**: Manager / System Service Wrapper.
- **Context**: `Context.FINGERPRINT_SERVICE`.
- **Communication**: Binder IPC (`IFingerprintService`).
- **Callback Handling**: Uses `FingerprintServiceReceiver` (Stub) to forward callbacks to `FingerprintCallback`.

## Detailed Functionality

### Core Operations
- **Authenticate**: `authenticate(...)`. Supports crypto objects, cancellation signals, and various options.
- **Detect**: `detectFingerprint(...)`.
- **Enroll**: `enroll(...)`. Handles enrollment logic and callbacks.
- **Remove**: `remove(...)` / `removeAll(...)`.
- **Challenge**: `generateChallenge(...)` / `revokeChallenge(...)`.
- **Reset Lockout**: `resetLockout(...)`.
- **Rename**: `rename(...)`.

### Properties & State
- **Get Enrolled**: `getEnrolledFingerprints(...)`.
- **Has Enrolled**: `hasEnrolledFingerprints(...)`.
- **Is Hardware Detected**: `isHardwareDetected()`.
- **Sensor Properties**: `getSensorProperties()`, `getSensorPropertiesInternal()`.
- **Power Button FPS**: `isPowerbuttonFps()`.

### Inner Classes
- **CryptoObject**: Wrapper for crypto primitives (Signature, Cipher, Mac, IdentityCredential, etc.).
- **AuthenticationResult**: Result data.
- **AuthenticationCallback**: Client interface.
- **EnrollmentCallback**: Client interface.
- **RemovalCallback**: Client interface.
- **FingerprintServiceReceiver**: Binder callback stub.

### Helper Methods
- `getErrorString(...)`: Maps `FINGERPRINT_ERROR_*` to resources.
- `getAcquiredString(...)`: Maps `FINGERPRINT_ACQUIRED_*` to resources.
- `createEnrollStageThresholds(...)`: Loads config for enrollment stages.

## Data Model
- **Service Interface**: `IFingerprintService`.
- **Sensors**: List of `FingerprintSensorPropertiesInternal`.

## Java-to-C++ Translation Guide
- **IPC**: Use `android::sp<IFingerprintService>`.
- **Callbacks**: Implement `BnFingerprintServiceReceiver` in C++.
- **Resources**: String/Array loading (`getEnrollStageThresholds`, `getErrorString`) relies on Android Resources. C++ porting needs a strategy for this (e.g. error codes only).

## Implementation Risks
- **Deprecated APIs**: Many methods are deprecated but still functional/used internally.
- **Permissions**: Enforces `USE_BIOMETRIC`, `USE_FINGERPRINT`, `MANAGE_FINGERPRINT`, `USE_BIOMETRIC_INTERNAL`.

