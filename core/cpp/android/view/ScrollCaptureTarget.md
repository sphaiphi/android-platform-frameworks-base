# ScrollCaptureTarget - Reverse Engineering Documentation

## Executive Summary
`ScrollCaptureTarget` is a contextual object that pairs a specific `View` with its `ScrollCaptureCallback`. It stores the metadata discovered during the "Search" phase of a scroll capture operation, including the view's current position, its scrollable bounds, and developer-provided hints.

## Data Model
*   **`mContainingView`**: The actual scrollable `View`.
*   **`mCallback`**: The app-provided logic for rendering scrollable content.
*   **`mScrollBounds`**: The rectangle describing the scrollable area in view-local coordinates.
*   **`mPositionInWindow`**: The screen-space location of the view.

## Detailed Functionality
*   **`updatePositionInWindow()`**: Refreshes the coordinates to ensure they are current at the start of a capture session.
*   **`setScrollBounds()`**: Intersects the requested bounds with the view's actual width/height to prevent out-of-bounds rendering.

## Java-to-C++ Translation Guide
*   **Pattern**: Context Holder.
*   **Lifecycle**: In C++, this object should be short-lived, existing only during the discovery and session-setup phases.

## Implementation Risks
*   **Dynamic Layout**: If the view's position or size changes between the search phase and the start of capture, the `mScrollBounds` will be stale.
