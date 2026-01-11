# AuthenticateOptions - Reverse Engineering Documentation

## Executive Summary
`AuthenticateOptions` is an interface that defines common authentication options exposed across various biometric modalities (fingerprint, face, iris). It provides a unified way to access context information like user ID, sensor ID, display state, and package attribution for authentication requests.

## Architecture Overview
This interface serves as a contract for configuration objects passed to authentication methods in the Biometric framework. Implementing classes (likely internal or hidden) would aggregate these parameters to ensure consistent behavior across the biometric stack.

## Detailed Functionality

### Option Accessors
- **User Identity**: `getUserId()` returns the target user for the operation.
- **Hardware Targeting**: `getSensorId()` specifies which biometric sensor is involved.
- **Context**: `getOpPackageName()` and `getAttributionTag()` provide identity for AppOps verification.
- **Display State**: `getDisplayState()` returns the current state of the display (Lockscreen, AOD, etc.), which is critical for optimization (e.g., UDFPS behavior).
- **Policy**: `isMandatoryBiometrics()` indicates if the auth is forced by a mandatory security policy.

## Data Model
- **Display State Constants**:
    - `DISPLAY_STATE_UNKNOWN` (0)
    - `DISPLAY_STATE_LOCKSCREEN` (1)
    - `DISPLAY_STATE_NO_UI` (2) (Off/Doze)
    - `DISPLAY_STATE_SCREENSAVER` (3)
    - `DISPLAY_STATE_AOD` (4)

## API Reference
- `int getUserId()`
- `int getSensorId()`
- `int getDisplayState()`
- `String getOpPackageName()`
- `String getAttributionTag()`
- `boolean isMandatoryBiometrics()`

## Java-to-C++ Translation Guide
- **Interface**: Map to a abstract base class or a struct `AuthenticateOptions` in C++.
- **Enums**: `DISPLAY_STATE_*` constants should be mapped to an `enum class DisplayState`.
- **Strings**: Use `std::string` or `android::String16` for package names and tags.

## Implementation Risks
- Ensuring `displayState` is accurately synchronized with the actual power manager state to avoid issues with screen-dependent sensors (like optical fingerprint).
