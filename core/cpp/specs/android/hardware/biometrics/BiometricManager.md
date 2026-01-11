# BiometricManager - Reverse Engineering Documentation

## Executive Summary
`BiometricManager` is the primary system service wrapper for querying biometric capabilities and status. It allows applications to check if the device supports biometrics, if the user has enrolled templates, and to authenticate with different security levels (Strong, Weak, Device Credential).

## Architecture Overview
It is a `SystemService` (`Context.BIOMETRIC_SERVICE`) that communicates with `IAuthService` via Binder. It exposes the `Authenticators` interface for defining security strengths.

## Detailed Functionality

### Authenticator Types (`Authenticators`)
Bitmask interface defining security levels:
- `BIOMETRIC_STRONG`: Class 3 (Keystore integration allowed).
- `BIOMETRIC_WEAK`: Class 2.
- `BIOMETRIC_CONVENIENCE`: Class 1.
- `DEVICE_CREDENTIAL`: PIN/Pattern/Password.
- `IDENTITY_CHECK`: Strict mode for high-risk environments.

### Capability Checking
- `canAuthenticate(int authenticators)`: Checks if the specified authenticators are available and enrolled. Returns `BIOMETRIC_SUCCESS` or various error codes (`HW_UNAVAILABLE`, `NONE_ENROLLED`, `NO_HARDWARE`).

### Strings and UI
- `getStrings(int authenticators)`: Returns a `Strings` object containing localized button labels, prompt messages, and setting titles based on the available authenticators.

### Internal/Test API
- `getSensorProperties()`: Retrieves details about sensors.
- `createTestSession()`: For testing via `BiometricTestSession`.
- `resetLockout()`: Resets authentication lockout.

## Data Model
- **Result Codes**: `BIOMETRIC_SUCCESS`, `ERROR_HW_UNAVAILABLE`, `ERROR_NONE_ENROLLED`, `ERROR_NO_HARDWARE`, `ERROR_SECURITY_UPDATE_REQUIRED`.

## API Reference
- `public int canAuthenticate(int authenticators)`
- `public Strings getStrings(int authenticators)`
- `public long getLastAuthenticationTime(int authenticators)`

## Java-to-C++ Translation Guide
- **Service Proxy**: Implement a client for `IAuthService`.
- **Bitmasks**: `Authenticators` constants should be defined in a shared header.
- **Permissions**: `USE_BIOMETRIC`, `USE_BIOMETRIC_INTERNAL`, `TEST_BIOMETRIC` checks must be enforced at the service boundary.

## Implementation Risks
- `canAuthenticate` logic is complex due to the combination of hardware state, user enrollment, and security settings.
- Deprecated APIs (`canAuthenticate()` without args) map to `BIOMETRIC_WEAK` but logging is involved.
