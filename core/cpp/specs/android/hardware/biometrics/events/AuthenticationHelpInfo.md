# AuthenticationHelpInfo - Reverse Engineering Documentation

## Executive Summary
`AuthenticationHelpInfo` is a Data Class (Parcelable) carrying "help" or "recoverable error" information. This is feedback provided to the user to fix their interaction with the sensor (e.g., "Clean sensor", "Move face closer").

## Architecture Overview
Used by `AuthenticationStateListener.onAuthenticationHelp`.

## Detailed Functionality

### Fields
- **Source**: `BiometricSourceType mBiometricSourceType`.
- **Reason**: `int mRequestReason`.
- **Help Code**: `int mHelpCode`. Maps to `Biometric*Constants` acquired codes (often "help" strings are derived from non-good acquired codes).
- **Message**: `String mHelpString`. Localized guidance string.

## Java-to-C++ Translation Guide
- **Struct**: `struct AuthenticationHelpInfo { BiometricSourceType type; int requestReason; int helpCode; std::string helpString; };`

## Implementation Risks
- None.
