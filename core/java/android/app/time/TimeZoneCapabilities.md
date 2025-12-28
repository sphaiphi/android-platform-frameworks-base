# TimeZoneCapabilities - Reverse Engineering Documentation

## Executive Summary
Describes user capabilities for Time Zone settings. Includes controls for Auto Detection, Geo Detection, Manual Setting, and Notifications.

## Architecture Overview
*   **Type**: `public final class` implementing `Parcelable`.
*   **Structure**: Builder pattern, immutable.
*   **Identity**: `UserHandle`.

## Detailed Functionality
*   **Capabilities**:
    *   `ConfigureAutoDetection`
    *   `UseLocation` (Special boolean, not a capability enum, represents Master Location Switch status)
    *   `ConfigureGeoDetection`
    *   `SetManualTimeZone`
    *   `ConfigureNotifications`
*   **Logic**: `tryApplyConfigChanges`
    *   Validates requested changes against capabilities.
    *   Checks: AutoDetection, GeoDetection, Notifications.
    *   Returns null if *any* requested change is not allowed.

## Data Model
*   `UserHandle mUserHandle`
*   `int mConfigureAutoDetection...`
*   `boolean mUseLocationEnabled`
*   ... (other capabilities)

## API Reference
*   `tryApplyConfigChanges`: Central permission logic.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard.
*   **Logic**: Port `tryApplyConfigChanges` exactly. Ensure `mUseLocationEnabled` is treated as a status field, not a capability to be checked against `CAPABILITY_NOT_APPLICABLE` (though it influences other capabilities).

## Test Cases & Validation
*   Request GeoDetection change. If `GeoDetectionCapability` is `NOT_SUPPORTED`, return null.
*   Request Manual change. If `SetManualCapability` is `NOT_ALLOWED`, return null (Note: `TimeConfiguration` doesn't handle manual set, `TimeManager` does `setManualTimeZone` directly, but `TimeZoneConfiguration` might technically hold related flags, though standard usage separates them).
    *   *Correction*: `TimeZoneConfiguration` holds settings. `SetManualTimeZone` capability is checked when *invoking* `setManualTimeZone`, not when updating config object, unless the config object tracks "manual mode" implicitly by "auto=false". The `tryApplyConfigChanges` here checks Auto, Geo, Notifications.

## Implementation Risks
*   Complexity of multiple feature flags interacting.
