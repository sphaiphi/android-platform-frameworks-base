# WindowMetricsController - Reverse Engineering Documentation

## Executive Summary
`WindowMetricsController` handles the logic for computing `WindowMetrics` (bounds and insets) for a specific `Context`. It handles current, maximum, and potential maximum metrics (the latter used for foldable device predictions).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class`
*   **Role**: Metrics Computer.

## Detailed Functionality

### `getCurrentWindowMetrics()` / `getMaximumWindowMetrics()`
**Logic**:
1.  Retrieves the current `Configuration` from `Resources`.
2.  Extracts bounds (either `getBounds` or `getMaxBounds`).
3.  Creates a `Supplier<WindowInsets>` that calls `getWindowInsetsFromServerForDisplay`.

### `getWindowInsetsFromServerForDisplay(...)`
**Logic**:
1.  Calls `IWindowManager.getWindowInsets`.
2.  Constructs an `InsetsState`.
3.  Calls `insetsState.calculateInsets` using the provided bounds and context metadata.

### `getPossibleMaximumWindowMetrics(int displayId)`
**Logic**:
Queries all "possible" display configurations (e.g., folded vs unfolded states) from the system server and computes metrics for each.

## Java-to-C++ Translation Guide

### Data Types
*   `WindowMetrics` -> C++ DTO.
*   `InsetsState` -> `android::InsetsState`.

### Dependencies
*   Relies heavily on `IWindowManager` (Binder).

## Implementation Risks
*   **Consistency**: Metrics must match exactly what `ViewRootImpl` or `WindowManager` would report for the same context.
