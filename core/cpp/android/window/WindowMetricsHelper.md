# WindowMetricsHelper - Reverse Engineering Documentation

## Executive Summary
`WindowMetricsHelper` provides static utility methods to perform common calculations using `WindowMetrics` objects, such as calculating bounds that exclude specific system bars.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` (Utility)
*   **Role**: Geometry logic helper.

## Detailed Functionality

### `getBoundsExcludingNavigationBarAndCutout(WindowMetrics)`
**Algorithm**:
1.  Get `WindowInsets` from metrics.
2.  Identify insets for `navigationBars()` and `displayCutout()`.
3.  Calculate `insetsIgnoringVisibility`.
4.  Subtract these insets from the total metrics bounds.
5.  Return the resulting `Rect`.

## Java-to-C++ Translation Guide
*   **Math**: Straightforward `Rect.inset` logic.

## Implementation Risks
*   None.
