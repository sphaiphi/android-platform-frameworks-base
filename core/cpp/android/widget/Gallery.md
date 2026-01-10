# Gallery - Reverse Engineering Documentation

## Executive Summary
`Gallery` is a deprecated horizontally scrolling list view that locks the selected item to the center. It behaves like a carousel.

## Architecture Overview
*   **Inheritance**: `AbsSpinner` -> `Gallery`.
*   **Status**: Deprecated (Use `RecyclerView` or `ViewPager`).
*   **Role**: Horizontal Center-Locked List.

## Detailed Functionality
*   **Layout**: Lays out children horizontally.
*   **Selection**: The item closest to the center is "selected".
*   **Fling**: Custom fling logic to snap items to the center slot.
*   **Drawing Order**: Draws the selected child last (on top) if overlapping is enabled.

## Java-to-C++ Translation Guide
*   **Carousel**: Implement using a standard horizontal list with custom snapping and center-alignment logic.

## Implementation Risks
*   **Performance**: The legacy Gallery was known for poor performance and memory usage compared to RecyclerView.
