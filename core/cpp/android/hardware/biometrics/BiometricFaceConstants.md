# BiometricFaceConstants - Reverse Engineering Documentation

## Executive Summary
`BiometricFaceConstants` defines constants specific to face authentication. It includes error codes, acquisition feedback codes, and accessibility feature flags. It maps generic biometric errors to face-specific contexts where applicable.

## Architecture Overview
Similar to `BiometricConstants`, this class provides static definitions. It handles the mapping of HAL-specific face error/acquired codes to the framework's representation.

## Detailed Functionality

### Feature Flags
- `FEATURE_REQUIRE_ATTENTION`: Require eye contact.
- `FEATURE_REQUIRE_REQUIRE_DIVERSITY`: Require diverse poses (accessibility).

### Face Error Codes (`FaceError`)
Superset of `BiometricConstants` with face-specific naming:
- `FACE_ERROR_HW_UNAVAILABLE`, `TIMEOUT`, `CANCELED`, `LOCKOUT`, etc.
- `FACE_ERROR_NOT_ENROLLED`: Specific to face.

### Face Acquired Codes (`FaceAcquired`)
Detailed feedback for face capture:
- Lighting: `TOO_BRIGHT`, `TOO_DARK`.
- Distance: `TOO_CLOSE`, `TOO_FAR`.
- Position: `TOO_HIGH`, `TOO_LOW`, `TOO_RIGHT`, `TOO_LEFT`.
- Gaze/Pose: `POOR_GAZE`, `PAN/TILT/ROLL_TOO_EXTREME`.
- Obstruction: `FACE_OBSCURED`, `DARK_GLASSES_DETECTED`, `MOUTH_COVERING_DETECTED`.
- `FACE_ACQUIRED_START`: Latency measurement marker.

## Java-to-C++ Translation Guide
- **Constants**: Map 1:1 to C++ constants.
- **Helper Methods**: `reasonToMetric` converts enrollment reasons to logging metrics; logic should be preserved if metrics are implemented in C++.

## Implementation Risks
- The sheer number of acquired codes requires a robust UI state machine to handle feedback strings without overwhelming the user.
