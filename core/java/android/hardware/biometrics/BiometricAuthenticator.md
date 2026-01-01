# BiometricAuthenticator - Reverse Engineering Documentation

## Executive Summary
`BiometricAuthenticator` is the common interface implemented by all biometric authentication classes (e.g., `FingerprintManager`, `FaceManager`). It defines the basic constants for biometric types and structures for identification and authentication results.

## Architecture Overview
This interface acts as a unifying layer for different biometric modalities. It provides definitions for modality types, identifiers, result containers, and the callback mechanism for authentication events.

## Detailed Functionality

### Modality Constants
Defines bit-flags for supported biometrics:
- `TYPE_NONE` (0)
- `TYPE_CREDENTIAL` (1): PIN/Pattern/Password.
- `TYPE_FINGERPRINT` (2)
- `TYPE_IRIS` (4)
- `TYPE_FACE` (8)
- `TYPE_ANY_BIOMETRIC`: Combination mask.

### Inner Classes
1.  **Identifier**: Abstract parcelable base for biometric IDs (name, biometricId, deviceId).
2.  **AuthenticationResult**: Container for the result of an auth operation.
    - Holds `CryptoObject`, `AuthenticationResultType` (Credential vs Biometric), `Identifier`, and `UserId`.
3.  **AuthenticationCallback**: Abstract class for receiving auth events.
    - `onAuthenticationError`: Unrecoverable error.
    - `onAuthenticationHelp`: Recoverable error (feedback).
    - `onAuthenticationFailed`: Biometric rejected.
    - `onAuthenticationAcquired`: Raw acquisition signal.

## Data Model
- **AuthenticationResultType**: Integer indicating if the auth was done via biometric or device credential.

## API Reference
- **Interface**: `BiometricAuthenticator`
- **Callback**: `AuthenticationCallback` methods.

## Java-to-C++ Translation Guide
- **Interface**: `BiometricAuthenticator` -> `IBiometricAuthenticator` (conceptually, though AIDL exists).
- **Constants**: Map `TYPE_*` to bitmask enums.
- **Identifier**: `struct BiometricIdentifier { string name; int id; long deviceId; }`.
- **Callbacks**: Use `std::function` or observer pattern.

## Implementation Risks
- ensuring `AuthenticationResult` correctly wraps the `CryptoObject` to maintain the keystore operation chain.
