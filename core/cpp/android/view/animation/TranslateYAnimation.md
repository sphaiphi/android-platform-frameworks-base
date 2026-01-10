# TranslateYAnimation - Reverse Engineering Documentation

## Executive Summary
Specialized TranslateAnimation that only affects Y. Preserves existing X translation from the transformation matrix.

## Key Algorithms
*   **`applyTransformation`**:
    *   Gets current matrix values.
    *   Interpolates dy.
    *   Sets translate using *existing* dx from matrix and calculated dy.

## Java-to-C++ Translation Guide
*   **Matrix**: Requires `getValues` access.
