# AuthenticationAcquiredInfo - Reverse Engineering Documentation

## Executive Summary
`AuthenticationAcquiredInfo` is a Data Class (Parcelable) that encapsulates information about a biometric "acquired" event. This event occurs when the sensor captures an image or signal, providing feedback on the quality or status of the acquisition (e.g., "partial", "dirty", "too fast") before the actual authentication result is determined.

## Architecture Overview
It is part of the `android.hardware.biometrics.events` package and is used primarily by the `AuthenticationStateListener` AIDL interface to broadcast events to system components (like SystemUI). It uses the `DataClass` annotation for boilerplate generation.

## Detailed Functionality

### Fields
- **Source**: `BiometricSourceType mBiometricSourceType` (Fingerprint, Face, Iris).
- **Reason**: `int mRequestReason` (Why auth was requested - Keyguard, BP, Settings, etc.).
- **Info Code**: `int mAcquiredInfo`. This maps to constants defined in `BiometricFaceConstants` or `BiometricFingerprintConstants` (e.g., `FACE_ACQUIRED_TOO_BRIGHT`).

## Java-to-C++ Translation Guide
- **Struct**: `struct AuthenticationAcquiredInfo { BiometricSourceType type; int requestReason; int acquiredInfo; };`
- **Serialization**: Standard Parcelable read/write.

## Implementation Risks
- None. Simple DTO.
