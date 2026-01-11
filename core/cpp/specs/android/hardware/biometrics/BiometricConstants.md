# BiometricConstants - Reverse Engineering Documentation

## Executive Summary
`BiometricConstants` is an interface containing modality-agnostic constants used throughout the biometric framework. It defines error codes, acquisition codes, and internal system event codes that are shared across Fingerprint, Face, and Iris subsystems.

## Architecture Overview
This file serves as a central repository for constant definitions to ensure consistency between the framework, HAL, and support libraries. It includes `IntDef` annotations for type safety.

## Detailed Functionality

### Error Codes (`Errors`)
Standardized errors returned by hardware or the framework:
- `BIOMETRIC_ERROR_HW_UNAVAILABLE`: Hardware busy/gone.
- `BIOMETRIC_ERROR_TIMEOUT`: Sensor timed out.
- `BIOMETRIC_ERROR_CANCELED`: Operation canceled.
- `BIOMETRIC_ERROR_LOCKOUT` / `LOCKOUT_PERMANENT`: Too many attempts.
- `BIOMETRIC_ERROR_USER_CANCELED`: User dismissed via UI.
- `BIOMETRIC_ERROR_NO_DEVICE_CREDENTIAL`: Security setup missing.
- `BIOMETRIC_ERROR_SECURITY_UPDATE_REQUIRED`: Security downgrade detected.
- `BIOMETRIC_ERROR_IDENTITY_CHECK_NOT_ACTIVE`: Identity check requirement failed.

### Acquired Codes (`Acquired`)
Feedback during image acquisition:
- `BIOMETRIC_ACQUIRED_GOOD`: Success.
- `BIOMETRIC_ACQUIRED_PARTIAL`, `INSUFFICIENT`, `IMAGER_DIRTY`: Image quality issues.
- `BIOMETRIC_ACQUIRED_TOO_SLOW`, `TOO_FAST`: Motion issues.

### Lockout Modes
- `BIOMETRIC_LOCKOUT_NONE`
- `BIOMETRIC_LOCKOUT_TIMED`
- `BIOMETRIC_LOCKOUT_PERMANENT`

## Java-to-C++ Translation Guide
- **Constants**: Map directly to C++ `enum class` or `static const int`.
- **Validation**: Ensure these constants match the AIDL/HIDL definitions exactly, as they are passed across binder boundaries.

## Implementation Risks
- Mismatches between these constants and vendor-specific HAL return codes can lead to incorrect UI feedback.
