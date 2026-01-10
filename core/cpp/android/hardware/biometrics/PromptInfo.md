# PromptInfo - Reverse Engineering Documentation

## Executive Summary
`PromptInfo` is a comprehensive Parcelable class that contains all the configuration data for a `BiometricPrompt`. It acts as the configuration payload sent from the app to the `AuthService`.

## Architecture Overview
Constructed via `BiometricPrompt.Builder`, but `PromptInfo` is the actual data object passed via AIDL.

## Detailed Functionality

### Fields
- **Visuals**: `mTitle`, `mSubtitle`, `mDescription` (CharSequences).
- **Logo**: `mLogoRes`, `mLogoBitmap`, `mLogoDescription`.
- **Content**: `mContentView` (Parcelable).
- **Buttons**: `mNegativeButtonText`.
- **Options**:
    - `mConfirmationRequested`: Require explicit confirm?
    - `mDeviceCredentialAllowed` / `mAuthenticators`: Auth types.
    - `mAllowedSensorIds`: Specific sensor targeting.
    - `mAllowBackgroundAuthentication`.
    - `mReceiveSystemEvents`.
- **Device Credential Fallback**: Custom title/subtitle/description for the PIN/Pattern screen.

### Permissions Logic
- `requiresAdvancedPermission()`: Checks if logo or custom content is used.
- `requiresInternalPermission()`: Checks if system-only features (custom title, disallow policy) are used.

## Java-to-C++ Translation Guide
- **Struct**: A large struct mirroring the fields.
- **Bitmap**: `Bitmap` parceling in C++ involves `Ashmem` or `HardwareBuffer`.
- **Lists**: `List<Integer>` -> `std::vector<int32_t>`.

## Implementation Risks
- Large parcelable overhead if bitmaps are large (though bitmaps should be small icons).
- Ensuring all fields are correctly serialized/deserialized across AIDL.
