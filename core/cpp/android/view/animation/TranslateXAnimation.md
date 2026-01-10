# TranslateXAnimation - Reverse Engineering Documentation

## Executive Summary
Specialized TranslateAnimation that only affects X. Preserves existing Y translation from the transformation matrix.

## Key Algorithms
*   **`applyTransformation`**:
    *   Gets current matrix values.
    *   Interpolates dx.
    *   Sets translate using calculated dx and *existing* dy from matrix.

## Java-to-C++ Translation Guide
*   **Matrix**: Requires `getValues` access.
