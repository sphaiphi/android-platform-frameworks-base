# PatternPathMotion - Reverse Engineering Documentation

## Executive Summary
A `PathMotion` that fits a supplied path pattern (e.g., "M0 0 L0 100 L100 100") between the start and end points.

## Logic
-   **Configuration**: Takes a `Path` pattern.
-   **`getPath`**:
    -   Measures the pattern's length and vector.
    -   Calculates a transformation matrix (Rotate + Scale + Translate) to map the pattern's start/end to the actual start/end points.
    -   Transforms the pattern path.

## Java-to-C++ Translation Guide
-   **Matrix**: Requires 2D affine transform matrix capabilities.
-   **Path**: Path parsing and transformation logic.
