# GhostView - Reverse Engineering Documentation

## Executive Summary
`GhostView` is a specialized internal view used to draw another `View` in a window's `Overlay` without changing its actual position in the view hierarchy. It is primarily used during transitions and animations to "float" a view on top of other content while its original parent remains unchanged.

## Architecture Overview
*   **Role**: Visual proxy for views during transitions.
*   **Rendering**: Directly draws the target view's `RenderNode` into the overlay's canvas.
*   **Visibility**: When a `GhostView` is active, it typically sets the original view to `INVISIBLE` to avoid double-rendering.

## Detailed Functionality

### 1. Creation and Management
*   **`addGhost()`**: Static method that creates a `GhostView`, wraps it in a `FrameLayout`, and inserts it into the target `ViewGroupOverlay`.
*   **`calculateMatrix()`**: Computes the transformation matrix required to align the ghosted view with its new host coordinate system.

### 2. Rendering
*   **`onDraw()`**: Uses `RecordingCanvas.drawRenderNode()` to efficiently replicate the visual state of the shadowed view.

### 3. Lifecycle
*   **Reference Counting**: Tracks how many components are currently using the ghost view to manage its removal.

## Java-to-C++ Translation Guide
*   **RenderNode**: This feature depends heavily on the hardware-accelerated rendering pipeline. In C++, use `android::uirenderer::RenderNode`.
*   **Matrix Math**: Requires precise global-to-local coordinate transformations.

## Implementation Risks
*   **Input Handling**: `GhostView` is visual-only; it does NOT receive touch or key events. This can lead to "non-interactive" UI if not used correctly during transitions.
*   **Hierarchy Sync**: If the original view's layout or content changes while ghosted, the `GhostView` must be invalidated to reflect those changes.
