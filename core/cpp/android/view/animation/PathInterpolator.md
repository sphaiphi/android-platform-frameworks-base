# PathInterpolator - Reverse Engineering Documentation

## Executive Summary
Interpolator that follows a `Path` (bezier curve) defined on (0,0) to (1,1).

## Key Algorithms
*   **`initPath`**: Approximates the path into X and Y arrays using `Path.approximate`.
*   **`getInterpolation`**: Finds the corresponding X in the array (binary search) and interpolates the Y value. Effectively maps X -> Y.

## Java-to-C++ Translation Guide
*   **Path**: Requires a Bezier curve implementation or flattening logic.
