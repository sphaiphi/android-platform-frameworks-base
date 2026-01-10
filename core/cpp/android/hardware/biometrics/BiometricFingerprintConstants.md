# BiometricFingerprintConstants - Reverse Engineering Documentation

## Executive Summary
`BiometricFingerprintConstants` defines constants specific to fingerprint authentication. It mirrors the structure of `BiometricConstants` but includes fingerprint-specific acquisition codes like "partial" or "immobile".

## Architecture Overview
Interface defining static integer constants used by `FingerprintManager` and related services.

## Detailed Functionality

### Fingerprint Error Codes (`FingerprintError`)
Standard errors mapped to fingerprint context:
- `FINGERPRINT_ERROR_HW_UNAVAILABLE`
- `FINGERPRINT_ERROR_BAD_CALIBRATION`: Sensor specific calibration error.

### Fingerprint Acquired Codes (`FingerprintAcquired`)
Feedback for finger placement:
- `FINGERPRINT_ACQUIRED_GOOD`
- `FINGERPRINT_ACQUIRED_PARTIAL`: Only part of the finger detected.
- `FINGERPRINT_ACQUIRED_IMAGER_DIRTY`: Sensor dirty.
- `FINGERPRINT_ACQUIRED_TOO_SLOW` / `TOO_FAST`: Swipe sensor feedback.
- `FINGERPRINT_ACQUIRED_IMMOBILE`: Finger not moving (for swipe) or stuck.
- `FINGERPRINT_ACQUIRED_POWER_PRESSED`: Side fingerprint sensor + power button interaction.

### Logic
- `shouldDisableUdfpsDisplayMode(int acquiredInfo)`: Helper to determine if the Under-Display Fingerprint Sensor (UDFPS) overlay should be disabled based on the acquisition status. Typically returns true for terminal acquisition states or errors.

## Java-to-C++ Translation Guide
- **Constants**: 1:1 mapping.
- **Logic**: Port `shouldDisableUdfpsDisplayMode` to the C++ logic controlling the UDFPS UI layer.

## Implementation Risks
- `FINGERPRINT_ACQUIRED_VENDOR` codes require careful handling to lookup vendor-specific strings.
