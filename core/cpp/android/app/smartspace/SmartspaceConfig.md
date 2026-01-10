# SmartspaceConfig - Reverse Engineering Documentation

## Executive Summary
`SmartspaceConfig` is a configuration object used to initialize a `SmartspaceSession`. It defines the parameters for the smartspace context, such as the UI surface name (e.g., "home", "lockscreen"), the desired number of predictions, and the client's package name.

## Architecture Overview
- **Package**: `android.app.smartspace`
- **Type**: `Parcelable` data class.
- **Role**: Configuration parameter passed to `SmartspaceManager.createSmartspaceSession`.

## Detailed Functionality

### Configuration Storage
**Purpose**: Holds immutable configuration settings for a session.
**Key Attributes**:
- **Target Count**: Hint to the backend for how many items to return.
- **UI Surface**: Identifier for where the results will be displayed.
- **Package Name**: Identity of the requesting application.
- **Extras**: Extensible bundle for additional config.

### Serialization
**Purpose**: Transmit configuration to the system service.
**Algorithm**: Standard Parcel read/write sequence (String, Int, String, Bundle).

## Data Model

| Field | Type | Description | Constraints |
|-------|------|-------------|-------------|
| `mSmartspaceTargetCount` | `int` | Expected number of targets | Range [0, 50] |
| `mUiSurface` | `String` | UI Surface identifier | Non-null |
| `mPackageName` | `String` | Client package name | Non-null |
| `mExtras` | `Bundle` | Additional config | Nullable |

## API Reference

### Getters
- `getSmartspaceTargetCount()`
- `getUiSurface()`
- `getPackageName()`
- `getExtras()`

### Builder
- `Builder(Context context, String uiSurface)`: Extracts package name from Context.
- `setSmartspaceTargetCount(int)`: Default is 5.
- `setExtras(Bundle)`: Default is `Bundle.EMPTY`.
- `build()`: Creates the config.

## Java-to-C++ Translation Guide

### Types
- `String` -> `android::String16` or `std::string` (UTF-8).
- `int` -> `int32_t`.
- `Bundle` -> `android::os::Bundle`.

### Dependencies
- The Builder in Java uses `android.content.Context` to get the package name. In C++, the package name might need to be passed explicitly if a Context equivalent isn't available.

## Test Cases & Validation
1.  **Defaults**: Verify default target count is 5.
2.  **Parceling**: Round-trip serialization test.
3.  **Equality**: Verify `equals()` and `hashCode()` implementation.

## Implementation Risks
- None significant. Standard POD (Plain Old Data) wrapper.
