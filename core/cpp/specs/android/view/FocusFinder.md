# FocusFinder - Reverse Engineering Documentation

## Executive Summary
`FocusFinder` is the core engine used by the Android UI toolkit to determine which View should receive focus next when a user navigates with a D-pad, trackball, or keyboard. It implements complex geometric algorithms to find the "nearest neighbor" in a given direction.

## Architecture Overview
*   **Role**: Navigation focus calculator.
*   **Singleton**: Thread-local singleton accessed via `getInstance()`.
*   **Strategy**: Uses a "beam" algorithm to prioritize views that are directly in the path of the navigation, then falls back to a weighted distance calculation.

## Detailed Functionality

### 1. Focus Search
*   **`findNextFocus(root, focused, direction)`**: The primary entry point. It searches through the focusable descendants of the root view.
*   **`findNextFocusFromRect(root, rect, direction)`**: Useful for finding focus from a specific point on the screen (e.g., after a touch).

### 2. The Nearest Neighbor Algorithm
*   **Candidate Check**: Filters views that are actually in the requested direction.
*   **Beam Beats**: Prioritizes views that overlap the "beam" projected from the current focused view.
*   **Weighted Distance**: For views outside the beam, uses a formula: `13 * majorAxis^2 + minorAxis^2`. This heavily weights distance in the direction of travel while allowing some lateral deviation.

### 3. Special Features
*   **User-Specified Focus**: Respects `nextFocusForward`, `nextFocusUp`, etc., attributes if defined by the developer.
*   **Cluster Navigation**: Handles "Keyboard Navigation Clusters" (jumps between groups of views).

## Java-to-C++ Translation Guide
*   **Geometry**: Requires a robust `Rect` and `Point` math library.
*   **Complexity**: The distance formula and beam logic are highly tuned; the C++ implementation should replicate the `13x^2 + y^2` weight exactly for consistent behavior.

## Implementation Risks
*   **Performance**: In very large view trees (e.g., complex lists), searching for the next focusable child can be O(N).
*   **RTL Support**: Must correctly swap Left/Right logic when the layout direction is Right-to-Left.
