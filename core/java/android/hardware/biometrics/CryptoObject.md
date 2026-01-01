# CryptoObject - Reverse Engineering Documentation

## Executive Summary
`CryptoObject` is a wrapper class that encapsulates various cryptographic primitives (`Signature`, `Cipher`, `Mac`, `KeyAgreement`, `PresentationSession`) or a raw operation handle. It serves as a bridge between the high-level Java crypto APIs and the low-level operation ID (`opId`) required by the Biometric Keystore integration.

## Architecture Overview
This class is the key to "Auth-per-use" keys. When `BiometricPrompt.authenticate` is called with a `CryptoObject`, the framework unlocks the underlying operation handle in Keystore only after successful authentication.

## Detailed Functionality

### Wrapping
It holds a generic `Object mCrypto`.
Constructors accept:
- `Signature`
- `Cipher`
- `Mac`
- `IdentityCredential` (Deprecated)
- `PresentationSession`
- `KeyAgreement`
- `long operationHandle`

### Operation ID Extraction (`getOpId`)
This is the most critical logic.
1. If `mCrypto` is null -> 0.
2. If `mCrypto` is `Long` -> return value.
3. If `IdentityCredential` -> call `getCredstoreOperationHandle()`.
4. If `PresentationSession` -> call `getCredstoreOperationHandle()`.
5. Else (JCA primitives) -> call `AndroidKeyStoreProvider.getKeyStoreOperationHandle(mCrypto)`.

## Java-to-C++ Translation Guide
- **Concept**: In C++, this object basically represents a `uint64_t operationId`. The complex Java object wrapping is to allow the Android Keystore Provider to track the session.
- **Usage**: When implementing `authenticate`, C++ code will likely just pass the `opId`.

## Implementation Risks
- `AndroidKeyStoreProvider` is internal API. Re-implementing this logic requires access to the underlying Keystore implementation details.
