# AuthenticationStoppedInfo - Reverse Engineering Documentation

## Executive Summary
`AuthenticationStoppedInfo` is a Data Class (Parcelable) indicating the end or cancellation of a biometric authentication session.

## Architecture Overview
Used by `AuthenticationStateListener.onAuthenticationStopped`.

## Detailed Functionality

### Fields
- **Source**: `BiometricSourceType mBiometricSourceType`.
- **Reason**: `int mRequestReason`.

## Java-to-C++ Translation Guide
- **Struct**: `struct AuthenticationStoppedInfo { BiometricSourceType type; int requestReason; };`

## Implementation Risks
- None.
