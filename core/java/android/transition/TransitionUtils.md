# TransitionUtils - Reverse Engineering Documentation

## Executive Summary
Static helper methods for transitions.

## Functions
-   **`mergeAnimators`**: Combines two animators into a set.
-   **`copyViewImage`**: Creates a bitmap snapshot of a view.
-   **`createDrawableBitmap`**: Extracts bitmap from drawable.
-   **`createViewBitmap`**: Renders view to canvas.

## Java-to-C++ Translation Guide
-   **Rasterization**: Critical helper for reparenting/crossfade effects. Requires rendering a node to an offscreen buffer.
