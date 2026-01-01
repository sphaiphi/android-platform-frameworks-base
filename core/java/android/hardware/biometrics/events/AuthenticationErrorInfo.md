# AuthenticationErrorInfo - Reverse Engineering Documentation

## Executive Summary
`AuthenticationErrorInfo` is a Data Class (Parcelable) that encapsulates information about an unrecoverable error during biometric authentication. This includes hardware unavailability, timeouts, or lockouts.

## Architecture Overview
Used by `AuthenticationStateListener.onAuthenticationError`.

## Detailed Functionality

### Fields
- **Source**: `BiometricSourceType mBiometricSourceType`.
- **Reason**: `int mRequestReason`.
- **Error Code**: `int mErrCode`. Maps to `BiometricConstants`, `BiometricFaceConstants`, or `BiometricFingerprintConstants` error definitions.
- **Message**: `String mErrString`. Localized, human-readable error message suitable for UI display.

## Java-to-C++ Translation Guide
- **Struct**: `struct AuthenticationErrorInfo { BiometricSourceType type; int requestReason; int errCode; std::string errString; };`

## Implementation Risks
- Ensure `errString` is properly localized/sanitized before display, though this object usually carries the string *from* the framework *to* the UI.
