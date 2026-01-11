# ConfigurationHelper - Reverse Engineering Documentation

## Executive Summary
`ConfigurationHelper` is a utility class containing static methods to determine *when* and *why* resources or layouts should be updated based on `Configuration` changes. It encapsulates logic for detecting significant changes like display rotation, bounds resizing, or locale switches.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Utility, static methods)
*   **Role**: Logic encapsulation for configuration diffing.

## Detailed Functionality

### `freeTextLayoutCachesIfNeeded(int configDiff)`
*   **Check**: `(configDiff & ActivityInfo.CONFIG_LOCALE) != 0`
*   **Action**: Calls `Canvas.freeTextLayoutCaches()`.

### `shouldUpdateResources(...)`
**Parameters**: Token, original config, new config, override config, displayChanged, configChanged.
**Logic**:
1.  If `config` is null, update.
2.  If `displayChanged` is true, update.
3.  If new config == old config AND override config unchanged (checked via `ResourcesManager`), don't update.
4.  If bounds changed (`shouldUpdateWindowMetricsBounds`), update.
5.  If rotation changed (`isDisplayRotationChanged`), update.
6.  Otherwise return `configChanged` (or diff check).

### `shouldUpdateWindowMetricsBounds(...)`
**Logic**: Compares `windowConfiguration.getBounds()` and `getMaxBounds()` between current and new configs.

### `isDisplayRotationChanged(...)`
**Logic**: Compares `windowConfiguration.getDisplayRotation()`. Ignores if undefined.

## Java-to-C++ Translation Guide

### Dependencies
*   `Configuration` class (C++ equivalent).
*   `ResourcesManager` (Java specific). The concept of "Resources" might map to an `AssetManager` or similar in C++, but the specific instance tracking is likely different.
*   `Canvas` (for text cache clearing).

### Logic Porting
*   The diffing logic (`diff`, `equals`) is portable assuming the C++ `Configuration` struct has equivalent comparison operators.

## Implementation Risks
*   **ResourcesManager**: This is a singleton in Java that manages `ResourcesImpl` cache. C++ might not have a direct equivalent or might use a different caching mechanism.
