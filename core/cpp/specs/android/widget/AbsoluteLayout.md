# AbsoluteLayout - Reverse Engineering Documentation

## Executive Summary
`AbsoluteLayout` is a deprecated layout container that allows children to be positioned at exact x/y coordinates. While simple, it is not responsive to different screen sizes or orientations.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `AbsoluteLayout`.
*   **Status**: Deprecated.
*   **Role**: Explicit positioning container.

## Detailed Functionality

### 1. Layout Params
*   **`AbsoluteLayout.LayoutParams`**: Contains `x` and `y` fields (integers) corresponding to the `layout_x` and `layout_y` XML attributes.

### 2. Measurement (`onMeasure`)
*   Iterates through all children.
*   Measures each child with `UNSPECIFIED` specs (asking them how big they want to be).
*   Calculates the total required width/height by finding the maximum `x + childWidth` and `y + childHeight`.

### 3. Layout (`onLayout`)
*   Iterates through children.
*   Calls `child.layout()` using the `x` and `y` from their LayoutParams as the top-left corner.

## Java-to-C++ Translation Guide
*   **Simple Implementation**: This is one of the easiest layouts to implement.
*   **Coordinate System**: Map `layout_x`/`layout_y` directly to the position during the layout pass.

## Implementation Risks
*   **None**: The logic is trivial. The risk is purely in usage (non-responsive UI).
