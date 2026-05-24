# FaceAuthenticateOptions - Reverse Engineering Documentation

## Executive Summary
`FaceAuthenticateOptions` is a configuration class used to specify various parameters when requesting face authentication or detection. It implements `AuthenticateOptions` and `Parcelable`. It includes settings for user ID, sensor ID, display state, authentication reason, wake reason, and operation context (package name, attribution tag).

## Architecture Overview
- **Type**: Data Class / Parcelable.
- **Implements**: `android.hardware.biometrics.AuthenticateOptions`, `android.os.Parcelable`.
- **Generation**: Uses `com.android.internal.util.DataClass` annotation to generate boilerplate code (Builder, getters, setters, Parcelable implementation, equals, hashCode).

## Detailed Functionality

### Fields
- `mUserId` (`int`): The user ID for the operation. Default: 0.
- `mSensorId` (`int`): The sensor ID. Default: -1.
- `mDisplayState` (`int`): Current display state (e.g., ON, OFF, DOZE). Uses `AuthenticateOptions.DisplayState` annotation. Default: `DISPLAY_STATE_UNKNOWN`.
- `mAuthenticateReason` (`int`): Reason for authentication (e.g., UNKNOWN, STARTED_WAKING_UP, PRIMARY_BOUNCER_SHOWN). Uses `@AuthenticateReason` IntDef. Default: `AUTHENTICATE_REASON_UNKNOWN`.
- `mWakeReason` (`int`): Power manager wake reason. Uses `@PowerManager.WakeReason`. Default: `WAKE_REASON_UNKNOWN`.
- `mOpPackageName` (`String`): Calling package name for AppOps verification. Default: "" (empty string).
- `mAttributionTag` (`String`): Attribution tag. Default: null.
- `mIsMandatoryBiometrics` (`boolean`): Whether mandatory biometrics are active.

### Constants (AuthenticateReason)
- `AUTHENTICATE_REASON_UNKNOWN` (0)
- `AUTHENTICATE_REASON_STARTED_WAKING_UP` (1)
- `AUTHENTICATE_REASON_PRIMARY_BOUNCER_SHOWN` (2)
- ... and others up to `AUTHENTICATE_REASON_UDFPS_POINTER_DOWN` (10).

## Data Model
- **Primitive types**: `int`, `boolean`.
- **String types**: `String`.

## API Reference
- **Builder**: `FaceAuthenticateOptions.Builder` to construct instances.
- **Getters**: `getUserId()`, `getSensorId()`, `getDisplayState()`, etc.
- **Setters**: `setSensorId()`, `setOpPackageName()`, `setAttributionTag()`, `setIsMandatoryBiometrics()`. Note: Not all fields have public setters; some are only set via Builder.
- **Parcelable**: `writeToParcel`, `describeContents`, `CREATOR`.

## Java-to-C++ Translation Guide
- **Class**: Create a C++ class `FaceAuthenticateOptions`.
- **Parcelable**: Implement `android::os::Parcelable`.
- **Enums**: Map `AUTHENTICATE_REASON_*` constants to a C++ enum.
- **Fields**:
    - `int` -> `int32_t`
    - `boolean` -> `bool`
    - `String` -> `android::String16` or `std::string`
- **Builder**: Implement a Builder pattern in C++ if immutability/convenience is desired, or just a struct with default values.

## Implementation Risks
- **Parceling Logic**: The generated code uses bitmasks (`flg`) to handle boolean flags and nullability. C++ implementation must match this exact bitmask logic for correct IPC.
    - `mIsMandatoryBiometrics`: `flg |= 0x80`
    - `mAttributionTag`: `flg |= 0x40` (presence check)
- **Validation**: Java code performs validation (e.g., `authenticateReason` check). C++ code receiving this Parcel should ideally perform similar validation.
