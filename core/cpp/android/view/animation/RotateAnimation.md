# RotateAnimation - Reverse Engineering Documentation

## Executive Summary
Animates the rotation of an object.

## Data Model
*   `mFromDegrees`, `mToDegrees`.
*   `mPivotX`, `mPivotY`: Center of rotation. Supports absolute/relative types.

## Key Algorithms
*   **`applyTransformation`**:
    *   Interpolates degrees.
    *   Calls `matrix.setRotate(degrees, pivotX, pivotY)`.

## Java-to-C++ Translation Guide
*   **Matrix**: Requires a Matrix class (e.g., SkMatrix).
