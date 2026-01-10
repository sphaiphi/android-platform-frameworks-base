# ScaleAnimation - Reverse Engineering Documentation

## Executive Summary
Animates the scale (X/Y) of an object.

## Data Model
*   `mFromX/Y`, `mToX/Y`.
*   `mPivotX`, `mPivotY`: Center of scaling.

## Key Algorithms
*   **`applyTransformation`**:
    *   Interpolates scale X and Y.
    *   Calls `matrix.setScale(sx, sy, pivotX, pivotY)`.

## Java-to-C++ Translation Guide
*   **Matrix**: Requires a Matrix class.
