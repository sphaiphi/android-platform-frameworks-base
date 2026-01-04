# ViewRootRectTracker - Reverse Engineering Documentation

## Executive Summary
`ViewRootRectTracker` is a utility used by `ViewRootImpl` to aggregate and track collections of rectangles (Rects) reported by various views in the hierarchy. It is commonly used for tracking "System Gesture Exclusion" zones or "Keep Clear" areas.

## Architecture Overview
*   **Role**: Global rectangle aggregator.
*   **Tracking Mechanism**: Maps views to their reported rectangles and handles the coordinate transformation from view-local to window-space.

## Detailed Functionality
*   **`updateRectsForView()`**: Marks a specific view's rectangles as "dirty" and schedules a re-calculation.
*   **`computeChanges()`**: Iterates through all tracked views, collects their current rectangles, transforms them into global coordinates, and detects if the total set has changed since the last update.

## Java-to-C++ Translation Guide
*   **Structure**: Uses a list of `ViewInfo` objects, each holding a `WeakReference<View>`.
*   **Math**: Requires `ViewParent::getChildVisibleRect` logic to correctly map coordinates up the tree.

## Implementation Risks
*   **Performance**: In a deep hierarchy with many tracked views, `computeChanges` can be O(N) where N is the number of views.
*   **Coordinate Drift**: Changes in parent view translations or scrolls must trigger a re-calculation in the tracker.
