# TranslateAnimation - Reverse Engineering Documentation

## Executive Summary
Animates the position (X/Y translation) of an object.

## Data Model
*   `mFromXDelta`, `mToXDelta`, `mFromYDelta`, `mToYDelta`.
*   Supports absolute/relative types.

## Key Algorithms
*   **`applyTransformation`**:
    *   Interpolates dx and dy.
    *   Calls `matrix.setTranslate(dx, dy)`.

## Java-to-C++ Translation Guide
*   **Matrix**: Requires a Matrix class.
