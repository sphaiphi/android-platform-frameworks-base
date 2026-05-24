# BiometricRequestConstants - Reverse Engineering Documentation

## Executive Summary
`BiometricRequestConstants` defines the reasons/contexts for a biometric request. This helps the system understand *why* authentication or enrollment is happening, which may affect UI behavior or logging.

## Detailed Functionality

### Request Reasons (`RequestReason`)
- `REASON_UNKNOWN` (0)
- `REASON_ENROLL_FIND_SENSOR` (1): User needs to locate the sensor.
- `REASON_ENROLL_ENROLLING` (2): Active enrollment.
- `REASON_AUTH_BP` (3): BiometricPrompt authentication.
- `REASON_AUTH_KEYGUARD` (4): Lockscreen/Keyguard authentication.
- `REASON_AUTH_OTHER` (5): Other internal auth.
- `REASON_AUTH_SETTINGS` (6): Authentication within Settings app.

## Java-to-C++ Translation Guide
- **Enum**: `enum class RequestReason : int32_t`.

## Implementation Risks
- None. Pure constant definitions.
