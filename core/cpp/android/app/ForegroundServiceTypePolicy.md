# ForegroundServiceTypePolicy - Reverse Engineering Documentation

## Executive Summary
`ForegroundServiceTypePolicy` enforces the policies regarding Foreground Service (FGS) types. It checks permissions, deprecation status, and disabled status for each type.

## Architecture Overview
*   **Pattern**: Policy / Strategy.
*   **Default**: `DefaultForegroundServiceTypePolicy` subclass.
*   **Data Structures**: `ForegroundServiceTypePolicyInfo` (holds policy for a specific type).

## Detailed Functionality
*   **Policy Info**: Maps FGS type (e.g., `LOCATION`, `CAMERA`) to:
    *   Deprecation Change ID.
    *   Disabled Change ID.
    *   Required Permissions (`all of` or `any of`).
    *   Permission Enforcement Flag (DeviceConfig).
*   **Checks**: `checkForegroundServiceTypePolicy`. Verifies permissions and flags.
*   **Permissions**: `ForegroundServiceTypePermission` abstract class with implementations:
    *   `RegularPermission`: Standard Manifest permission.
    *   `AppOpPermission`: AppOp check.
    *   `RolePermission`: Role Manager check.
    *   `UsbDevicePermission` / `UsbAccessoryPermission`.

## Java-to-C++ Translation Guide
*   **Policy Engine**: Implement the checking logic.
*   **Static Data**: The policy definitions (mappings of types to permissions) can be static data structures.

## Implementation Risks
*   **Complexity**: The permission logic (`RegularPermission`, `AppOpPermission`) involves cross-checks with multiple system services.
