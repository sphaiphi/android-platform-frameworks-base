# ImsConfigurationTracker - Reverse Engineering Documentation

## Executive Summary
`ImsConfigurationTracker` helps `InputMethodService` manage configuration changes. It determines whether a configuration change (like orientation or locale) requires the IME service to be reset/restarted, based on the flags set in `android.R.styleable.InputMethod_configChanges`.

## Architecture Overview
*   **Role**: Logic helper for `InputMethodService`.

## Detailed Functionality
*   **`onInitialize`**: Sets the `mHandledConfigChanges` mask (from metadata).
*   **`onBindInput`**: Snapshots the current configuration (`mLastKnownConfig`) from the Resources.
*   **`onConfigurationChanged`**:
    *   Compares new config with `mLastKnownConfig`.
    *   Calculates `unhandledDiff` = `diff & ~mHandledConfigChanges`.
    *   If `unhandledDiff != 0`, runs the `resetStateForNewConfigurationRunner` (which usually triggers `initializeInternal` in IMS).
    *   Updates `mLastKnownConfig`.

## Data Model
*   `mLastKnownConfig`: The last configuration processed.
*   `mHandledConfigChanges`: Bitmask of config changes the IME claims to handle itself.

## Java-to-C++ Translation Guide
*   **Configuration**: C++ needs access to `AssetManager` / `ResTable` equivalent to diff configurations.
*   **Logic**: Pure logic translation.

## Implementation Risks
*   **Initialization**: Must ensure `onInitialize` is called before config changes are processed.
