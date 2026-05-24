# ViewOverlay - Reverse Engineering Documentation

## Executive Summary
`ViewOverlay` provides an extra rendering layer that sits on top of a `View` (or `ViewGroup`). it allows for adding "transient" visual elements like drawables or views that are drawn after all other content in the view hierarchy. it is the primary mechanism for implementing effects that need to float over standard UI components (e.g., drag-and-drop shadows, or "ghost" views during transitions).

## Architecture Overview
*   **Role**: Top-level visual decorator.
*   **Implementation**: `OverlayViewGroup` - a specialized internal `ViewGroup` that hosts the overlay content.
*   **Relationship**: The overlay is NOT a child of the host view but is rendered during the host's `dispatchDraw` pass.

## Detailed Functionality

### 1. Content Management
*   **`add(Drawable)`**: Inserts a drawable into the overlay.
*   **`add(View)`**: (Only via `ViewGroupOverlay`) Inserts a view into the overlay. Note that views in the overlay are visual-only; they do not receive input events.

### 2. Invalidation Redirection
*   Since the overlay is not in the standard parent-child hierarchy, `OverlayViewGroup` overrides `invalidate()` to manually redirect invalidation signals back to the host view.

### 3. Coordinate Handling
*   When a `View` is added to an overlay, its coordinates are automatically re-calculated to remain in the same relative screen position as its original parent.

## Java-to-C++ Translation Guide
*   **Pattern**: Decorator / Composite.
*   **Rendering**: In C++, the overlay should be implemented as a separate `RenderNode` that is always drawn last in the host's display list.

## Implementation Risks
*   **Input Blocking**: Developers often expect overlay views to be interactive; the C++ implementation must clearly document that they are visual proxies only.
*   **Resource Leak**: Contents added to the overlay must be cleared when the host view is detached to prevent memory leaks.
