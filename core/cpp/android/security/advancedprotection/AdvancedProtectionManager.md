# AdvancedProtectionManager - Reverse Engineering Documentation

## Executive Summary
`AdvancedProtectionManager` allows querying and controlling the "Advanced Protection" mode on the device. This mode enhances security by restricting certain features (like 2G, unknown sources, USB, etc.).

## Architecture Overview
*   **Package**: `android.security.advancedprotection`
*   **Type**: Class (System Service, System API)
*   **Service Name**: `Context.ADVANCED_PROTECTION_SERVICE`
*   **Dependencies**: `IAdvancedProtectionService` (AIDL).

## Detailed Functionality

### 1. State Management
*   **Method**: `isAdvancedProtectionEnabled()`
*   **Method**: `setAdvancedProtectionEnabled(boolean enabled)`
*   **Method**: `getAdvancedProtectionFeatures()`
*   **Description**: Queries or sets the global enabled state, and retrieves the list of active protection features.

### 2. Notifications/Callbacks
*   **Method**: `registerAdvancedProtectionCallback` / `unregisterAdvancedProtectionCallback`
*   **Description**: Allows apps to listen for state changes. Uses an internal map (`mCallbackMap`) to manage `IAdvancedProtectionCallback` stubs.

### 3. UI Support
*   **Method**: `createSupportIntent` / `createSupportIntentForPolicyIdentifierOrRestriction`
*   **Description**: Generates an `Intent` to show a dialog explaining why an action was blocked. Used by other system components when they block an action due to this policy.
*   **Method**: `logDialogShown`
*   **Description**: Logs that the support dialog was shown.

## Java-to-C++ Translation Guide
*   **IPC**: Interact with `IAdvancedProtectionService`.
*   **Callbacks**: Implement `IAdvancedProtectionCallback` for C++ clients if needed.
*   **Constants**: Mirror the `FEATURE_ID_*` constants.
