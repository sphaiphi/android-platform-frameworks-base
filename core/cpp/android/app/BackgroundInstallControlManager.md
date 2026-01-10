# BackgroundInstallControlManager - Reverse Engineering Documentation

## Executive Summary
`BackgroundInstallControlManager` provides access to the `BackgroundInstallControlService`. It allows privileged apps to query which packages were installed in the background (without user interaction).

## Architecture Overview
*   **Pattern**: Manager/Service Client.
*   **Dependencies**: `IBackgroundInstallControlService`.

## Detailed Functionality
*   `getBackgroundInstalledPackages(long flags)`:
    *   Calls service `getBackgroundInstalledPackages`.
    *   Returns `List<PackageInfo>`.
    *   Requires `GET_BACKGROUND_INSTALLED_PACKAGES` permission.

## Java-to-C++ Translation Guide
*   Standard Binder proxy wrapper.

## Implementation Risks
*   None.
