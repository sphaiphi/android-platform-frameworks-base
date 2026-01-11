# SystemConfigManager - Reverse Engineering Documentation

## Executive Summary
`SystemConfigManager` provides access to the system configuration data loaded from XML files (like `/system/etc/sysconfig/*` and `/system/etc/permissions/*`). It allows querying enabled components, disabled apps, and special permission grants.

## Architecture Overview
-   **Role**: Configuration Reader Client.
-   **Service**: `ISystemConfig` (Binder).
-   **Server**: `SystemConfigService` (in system_server), which wraps `SystemConfig` (internal class parsing the XMLs).

## API Reference
-   `getDisabledUntilUsedPreinstalledCarrierApps()`: Bloatware management.
-   `getSystemPermissionUids(String permission)`: Maps permissions to UIDs (e.g., for shared UIDs defined in platform.xml).
-   `getEnabledComponentOverrides(String packageName)`: Components enabled by config.
-   `getPreventUserDisablePackages()`: Apps user can't disable.

## Java-to-C++ Translation Guide
-   **Binder**: Call `ISystemConfig`.
-   **Direct Access**: If running as a system daemon with access to `/system/etc`, one could parse the XMLs directly, but going through the service ensures consistency with the framework.

## Implementation Risks
-   **Boot Dependency**: This service is available early, but the underlying data is static per boot.
