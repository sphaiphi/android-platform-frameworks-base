# ViewGroupOverlay - Reverse Engineering Documentation

## Executive Summary
`ViewGroupOverlay` extends `ViewOverlay` to allow adding `View`s (not just `Drawable`s) to the overlay layer of a `ViewGroup`. It is used for complex animations where a view needs to "float" above the entire container hierarchy without being constrained by the container's layout logic.

## Architecture Overview
*   **Inheritance**: `ViewOverlay` -> `ViewGroupOverlay`.
*   **Implementation**: Relies on the shared `OverlayViewGroup` internal class.

## Detailed Functionality
*   **`add(View)`**: Adds a view to the overlay.
    *   If the view has a parent, it is removed from that parent.
    *   The view's position is adjusted to appear visually in the same screen location, compensating for the difference between the old parent's coordinate space and the overlay's coordinate space.
*   **`remove(View)`**: Removes the view from the overlay.

## Java-to-C++ Translation Guide
*   **Pattern**: Composite.
*   **Coordinate Math**: The "re-parenting" logic requires precise `getLocationOnScreen` calculations to prevent the view from jumping visually.

## Implementation Risks
*   **Input**: Views in the overlay generally do *not* receive input events (as the overlay is often just a rendering layer). This behavior should be documented or replicated.
