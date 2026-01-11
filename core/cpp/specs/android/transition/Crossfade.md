# Crossfade - Reverse Engineering Documentation

## Executive Summary
`Crossfade` transitions between two views using bitmaps. It's useful when the view content changes completely or views are replaced.

## Data Model
-   **Behaviors**: `FADE_BEHAVIOR_CROSSFADE`, `FADE_BEHAVIOR_REVEAL`, `FADE_BEHAVIOR_OUT_IN`.
-   **Resize**: `RESIZE_BEHAVIOR_SCALE` (animates bounds) vs NONE.

## Key Algorithms
-   **`captureValues`**: Snapshots the view into a `Bitmap` and wraps it in a `BitmapDrawable`.
-   **`createAnimator`**:
    -   Adds drawables to `ViewOverlay`.
    -   Animates alpha of drawables based on behavior (e.g., crossfade = start goes 255->0, end goes 0->255).
    -   Animates bounds if resize behavior is set.

## Java-to-C++ Translation Guide
-   **Snapshotting**: Needs a way to rasterize a UI node to a texture/bitmap.
-   **Overlays**: Relies heavily on `ViewOverlay` to draw on top of the scene.
