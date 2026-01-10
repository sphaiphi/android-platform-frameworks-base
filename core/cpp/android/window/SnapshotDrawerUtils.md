# SnapshotDrawerUtils - Reverse Engineering Documentation

## Executive Summary
`SnapshotDrawerUtils` contains the logic for rendering a `TaskSnapshot` (bitmap/buffer of a previous task state) into a `SurfaceControl`. It handles scaling, letterboxing, and drawing system bar backgrounds if the snapshot doesn't fill the screen.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Utility)
*   **Role**: Renderer / Helper.
*   **Key Classes**: `SnapshotSurface`, `SystemBarBackgroundPainter`.

## Detailed Functionality

### `SnapshotSurface`
*   **Constructor**: Takes root surface, snapshot, window bounds.
*   **`drawSnapshot`**:
    *   Calculates if `sizeMismatch`.
    *   **Match**: Calls `transaction.setBuffer(root, buffer)`.
    *   **Mismatch**: Creates a child surface (BLAST layer). Scales it to fit the container. Sets the buffer on the child.

### `SystemBarBackgroundPainter`
*   **Purpose**: Fills the gap left by the snapshot in the status bar / nav bar areas (often needed if the snapshot was taken without decorations or in a different mode).
*   **Logic**: Uses `Canvas` (software drawing) to draw rectangles with system bar colors derived from `TaskDescription`.

## Java-to-C++ Translation Guide

### SurfaceControl
*   Translate `SurfaceControl.Transaction` calls to `SurfaceComposerClient::Transaction`.
    *   `setBuffer` -> `setBuffer`
    *   `setColorSpace` -> `setDataSpace` / `setColorSpace`
    *   `setScale` -> `setMatrix`

### Canvas
*   The `SystemBarBackgroundPainter` uses `Canvas`. In C++, drawing logic usually implies Skia or HWUI usage, or drawing to a separate `SurfaceControl` with a solid color.
*   **Optimisation**: Instead of drawing a canvas, C++ implementation typically creates a dim/color layer `SurfaceControl` for the background colors if they are solid rects.

## Implementation Risks
*   **Buffer Lifecycle**: Ensure the `HardwareBuffer` from the snapshot is not closed prematurely while the transaction is applying.
