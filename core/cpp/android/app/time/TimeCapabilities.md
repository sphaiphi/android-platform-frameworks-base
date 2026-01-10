# TimeCapabilities - Reverse Engineering Documentation

## Executive Summary
Describes the capabilities of a specific user regarding "Time" settings. Specifically, whether they can configure "Auto Time Detection" and "Manual Time".

## Architecture Overview
*   **Type**: `public final class` implementing `Parcelable`.
*   **Pattern**: Builder pattern for construction.
*   **Identity**: Tied to a specific `UserHandle`.

## Detailed Functionality
*   **Capabilities**:
    *   `ConfigureAutoDetectionEnabled`: Can the user toggle "Set time automatically"?
    *   `SetManualTime`: Can the user manually set the time (usually requires Auto=Off)?
*   **Logic**: `tryApplyConfigChanges(currentConfig, requestedChanges)`
    *   Checks if the user has the capability to make the requested change.
    *   If capability < `NOT_APPLICABLE` (i.e., NOT_SUPPORTED or NOT_ALLOWED), the change is rejected (returns null).
    *   Otherwise, returns a new `TimeConfiguration` with the change applied.

## Data Model
*   `UserHandle mUserHandle`
*   `int mConfigureAutoDetectionEnabledCapability`
*   `int mSetManualTimeCapability`

## API Reference
*   `tryApplyConfigChanges(...)`: Core logic for permission checking before configuration update.
*   Getters for capabilities.

## Java-to-C++ Translation Guide
*   **Parcelable**: Binder support.
*   **Logic**: Port `tryApplyConfigChanges` carefully. It acts as a gatekeeper.
    *   Logic: `if (req.hasChange() && capability < CAPABILITY_NOT_APPLICABLE) return nullptr;`

## Test Cases & Validation
*   User has `NOT_ALLOWED` for AutoDetect -> Requesting change returns `null`.
*   User has `POSSESSED` -> Requesting change returns new Config object.

## Implementation Risks
*   `UserHandle` mapping in C++ (often just `userid_t` or `int`).
