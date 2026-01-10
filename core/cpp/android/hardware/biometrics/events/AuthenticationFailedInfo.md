# AuthenticationFailedInfo - Reverse Engineering Documentation

## Executive Summary
`AuthenticationFailedInfo` is a Data Class (Parcelable) representing a failed authentication attempt (biometric rejected/not recognized).

## Architecture Overview
Used by `AuthenticationStateListener.onAuthenticationFailed`. Unlike errors, a "failure" implies the hardware worked but the biometric data did not match the enrolled template.

## Detailed Functionality

### Fields
- **Source**: `BiometricSourceType mBiometricSourceType`.
- **Reason**: `int mRequestReason`.
- **User**: `int mUserId`. Identifies which user failed authentication (relevant for multi-user devices).

## Java-to-C++ Translation Guide
- **Struct**: `struct AuthenticationFailedInfo { BiometricSourceType type; int requestReason; int userId; };`

## Implementation Risks
- None.
