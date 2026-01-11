# ExtendAnimation - Reverse Engineering Documentation

## Executive Summary
An animation that controls the `Insets` (outsets) of a Transformation. Similar to ClipRect but for insets.

## Data Model
*   `mFromInsets`, `mToInsets`.

## Key Algorithms
*   **`applyTransformation`**: Interpolates Inset values.

## Java-to-C++ Translation Guide
*   **Insets**: Struct for (left, top, right, bottom).
