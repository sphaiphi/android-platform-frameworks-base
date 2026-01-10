# AndroidDeviceConfig - Reverse Engineering Documentation

## Executive Summary
`AndroidDeviceConfig` defines keys for the `DeviceConfig` provider specifically for the `android` namespace. These keys control core system behaviors like gesture exclusion limits.

## Architecture Overview
- **Type**: Constant Interface.
- **Role**: Defines configuration keys for `DeviceConfig`.

## Data Model
-   **Keys**:
    -   `KEY_SYSTEM_GESTURE_EXCLUSION_LIMIT_DP`: Integer limit for gesture exclusion in dp.
    -   `KEY_SYSTEM_GESTURES_EXCLUDED_BY_PRE_Q_STICKY_IMMERSIVE`: Boolean flag for legacy behavior.

## Java-to-C++ Translation Guide
-   **Strings**: Simple string constants.
