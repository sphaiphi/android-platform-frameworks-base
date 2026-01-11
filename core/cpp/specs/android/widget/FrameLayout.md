# FrameLayout - Reverse Engineering Documentation

## Executive Summary
`FrameLayout` is a simple layout container designed to block out an area on the screen to display a single item. While it can hold multiple children, they are drawn in a stack (Z-order) based on the order they were added, with the latest child on top. It is commonly used as a container for fragments or to create simple overlays.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `FrameLayout`.
*   **Stacking Model**: Children are layered one on top of another.
*   **Sizing**: The layout's size is determined by its largest child (plus padding).

## Detailed Functionality

### 1. Measurement Logic
`FrameLayout` iterates through all non-GONE children (or all children if `measureAllChildren` is true):
1.  **Child Measurement**: Calls `measureChildWithMargins()` for each child.
2.  **Size Aggregation**: Tracks the maximum width and height among all children.
3.  **Match Parent Resolution**: If any child is set to `MATCH_PARENT` but the `FrameLayout` itself is `WRAP_CONTENT`, a second measurement pass is performed on those children once the final layout size is known to ensure they fill the space correctly.

### 2. Layout Logic
*   **Gravity Application**: Each child's position is determined by its `layout_gravity`.
    *   Horizontal: `LEFT`, `CENTER_HORIZONTAL`, `RIGHT`.
    *   Vertical: `TOP`, `CENTER_VERTICAL`, `BOTTOM`.
*   **Padding & Margins**: Respects both the parent's padding and the child's margins when calculating the final `l, t, r, b` coordinates.

### 3. Foreground Support
*   Historically, `FrameLayout` provided specialized support for foreground drawables (e.g., a ripple or a border), though much of this logic has been moved to the base `View` class in recent versions.

## Data Model
*   **`FrameLayout.LayoutParams`**: Extends `MarginLayoutParams`. Adds the `gravity` field to control the child's position within the stack.

## Java-to-C++ Translation Guide
*   **Stack Rendering**: In C++, iterate through the child list and render them in order.
*   **Gravity Solving**: Use the standard `android::Gravity` utility functions to calculate child offsets within the parent bounds.
*   **Optimization**: Skip the second measurement pass if the parent has an exact size (`MeasureSpec.EXACTLY`).

## Implementation Risks
*   **Overdraw**: Stacking multiple large, opaque children in a `FrameLayout` causes significant overdraw, wasting GPU cycles.
*   **Layout Bloat**: Using `FrameLayout` for complex positioning (instead of `RelativeLayout` or `ConstraintLayout`) leads to deeply nested hierarchies which are harder to maintain and slower to layout.
