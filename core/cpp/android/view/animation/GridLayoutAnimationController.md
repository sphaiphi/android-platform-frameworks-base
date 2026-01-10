# GridLayoutAnimationController - Reverse Engineering Documentation

## Executive Summary
Assigns animation delays to children of a `GridLayout` (or GridView). Delays depend on row/column indices and a direction priority.

## Key Algorithms
*   **`getDelayForView`**:
    *   Calculates row/column index.
    *   Applies delay formula based on `DIRECTION_` and `PRIORITY_` flags.
    *   Example (Column priority): `row * rowDelay + column * rowsCount * rowDelay`.

## Java-to-C++ Translation Guide
*   **Logic**: Pure math/logic. Requires access to child LayoutParams.
