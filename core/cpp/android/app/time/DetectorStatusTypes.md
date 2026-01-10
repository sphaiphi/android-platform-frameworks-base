# DetectorStatusTypes - Reverse Engineering Documentation

## Executive Summary
Defines constants and validation utility methods for the status of time and time zone detectors and their internal algorithms. It provides a shared vocabulary for describing whether a detector (like Location Time Zone Detector) is running, supported, or stopped.

## Architecture Overview
*   **Type**: `public final class` (Utility)
*   **Role**: Central definition of status codes and string conversion logic.
*   **Dependencies**: `android.text.TextUtils` (string checks).

## Detailed Functionality

### Status Codes
Two categories of status:
1.  **Detector Status**: Overall status of a detector service.
    *   `UNKNOWN` (0)
    *   `NOT_SUPPORTED` (1)
    *   `NOT_RUNNING` (2)
    *   `RUNNING` (3)
2.  **Algorithm Status**: Status of specific algorithms within a detector (e.g., Telephony vs. Location).
    *   Same values (0-3) mirrored as `DETECTION_ALGORITHM_STATUS_*`.

### Validation & Conversion
*   **Validation**: `requireValidDetectorStatus` and `requireValidDetectionAlgorithmStatus` throw `IllegalArgumentException` for out-of-bounds values.
*   **String Conversion**: `toString` and `fromString` methods for serialization/debugging (e.g., parsing shell commands).

## Data Model
*   **Type**: `int` representing enums.

## API Reference
*   `int requireValidDetectorStatus(int)`
*   `String detectorStatusToString(int)`
*   `int detectorStatusFromString(String)`
*   (Equivalents for `DetectionAlgorithmStatus`)

## Java-to-C++ Translation Guide
*   **Enums**: Create `enum class DetectorStatus : int32_t` and `enum class DetectionAlgorithmStatus : int32_t`.
*   **Validation**: Implement helper functions `IsValid(...)` or `EnsureValid(...)`.
*   **String Handling**:
    *   Use `std::string` or `const char*` for return types.
    *   Replace `TextUtils.isEmpty` with `str.empty()`.
    *   Throw `std::invalid_argument` or return `std::optional`/`Result` types instead of exceptions if preferred in C++ codebase style.

## Test Cases & Validation
*   Input `0`, `1`, `2`, `3` -> Valid.
*   Input `-1`, `4` -> Exception/Error.
*   String "RUNNING" -> `3`.
*   String "INVALID" -> Exception/Error.

## Implementation Risks
*   Ensure integer values match exactly as they may be serialized/IPC'd.
