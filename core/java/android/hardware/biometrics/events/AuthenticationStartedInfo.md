# AuthenticationStartedInfo - Reverse Engineering Documentation

## Executive Summary
`AuthenticationStartedInfo` is a Data Class (Parcelable) indicating the start of a biometric authentication session.

## Architecture Overview
Used by `AuthenticationStateListener.onAuthenticationStarted`.

## Detailed Functionality

### Fields
- **Source**: `BiometricSourceType mBiometricSourceType`.
- **Reason**: `int mRequestReason`.

## Java-to-C++ Translation Guide
- **Struct**: `struct AuthenticationStartedInfo { BiometricSourceType type; int requestReason; };`

## Implementation Risks
- None.
