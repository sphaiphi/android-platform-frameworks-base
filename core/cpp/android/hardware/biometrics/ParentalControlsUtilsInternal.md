# ParentalControlsUtilsInternal - Reverse Engineering Documentation

## Executive Summary
`ParentalControlsUtilsInternal` provides helper methods to determine if biometric authentication is disabled due to parental controls (Device Policy). It checks if keyguard features (Face/Fingerprint/Iris) are disabled by an admin.

## Architecture Overview
Static utility class. Depends on `DevicePolicyManager` and `SupervisionManager`.

## Detailed Functionality

### `parentConsentRequired(...)`
1. **Test Override**: Checks for `TEST_ALWAYS_REQUIRE_CONSENT_PACKAGE/CLASS` secure settings (debug only).
2. **Supervision Check**: Uses `SupervisionManager` to see if the user is supervised.
3. **DPM Check**: Calls `dpm.getKeyguardDisabledFeatures()`.
4. **Flag Matching**: Checks if `KEYGUARD_DISABLE_FINGERPRINT`, `_FACE`, or `_IRIS` flags are set in the disabled features bitmask.
5. **Result**: Returns `true` if the specific modality requested is disabled by DPM.

## Java-to-C++ Translation Guide
- **DPM Interaction**: Requires binding to `IDevicePolicyManager`.
- **Flags**: Map `DevicePolicyManager` constants to C++ bitmasks.

## Implementation Risks
- Dependency on the deprecated `getSupervisionComponentName` or new `SupervisionManager` flags requires handling different Android versions/flags.
