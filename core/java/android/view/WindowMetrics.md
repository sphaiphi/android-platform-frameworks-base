# WindowMetrics - Reverse Engineering Documentation

## Executive Summary
`WindowMetrics` provides physical and logical measurements for a specific window or a UI context. it encapsulates the bounds of the window and the current set of `WindowInsets`, allowing applications to perform precise layout calculations that account for system bars and display cutouts.

## Data Model
*   **`mBounds`**: `Rect` - The total area occupied by the window in pixels.
*   **`mWindowInsets`**: `WindowInsets` - The regions of the window obscured by the system.
*   **`mDensity`**: `float` - The display density associated with the window.

## Detailed Functionality
*   **`getBounds()`**: Returns the physical pixel size of the window. Note that this can vary significantly between standard activities and multi-window modes.
*   **`getWindowInsets()`**: Provides the insets required to avoid overlapping system UI.
*   **`getDensity()`**: Essential for converting between DP and PX.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `class WindowMetrics`.
*   **Calculation**: In C++, provide helpers to calculate DP-independent dimensions: `width / density`.

## Implementation Risks
*   **Stale Metrics**: Metrics are a snapshot of the system state at the time of retrieval. Apps must re-query metrics if the configuration (e.g., orientation) changes.
