# LinearLayout - Reverse Engineering Documentation

## Executive Summary
`LinearLayout` is a fundamental layout container that arranges its children in a single direction, either **horizontally** or **vertically**. It supports weight-based distribution of space, alignment via gravity, and baseline alignment for text-based components.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `LinearLayout`.
*   **Key Parameters**:
    *   `mOrientation`: `HORIZONTAL` (0) or `VERTICAL` (1).
    *   `mGravity`: Controls how children are aligned within the layout (e.g., `CENTER`, `BOTTOM`).
    *   `mWeightSum`: Total weight available for distribution.

## Detailed Functionality

### 1. Measurement Strategy
`LinearLayout` performs a specialized measurement pass based on its orientation (`measureVertical` or `measureHorizontal`):
*   **Weight Distribution**: If children have `layout_weight > 0`, the layout first measures children without weight, then distributes the remaining excess space among weighted children based on their proportion of the `weightSum`.
*   **Largest Child Optimization**: If `measureWithLargestChild` is enabled, all weighted children are treated as having the minimum size of the largest child in the group.

### 2. Layout Strategy
*   **Sequential Positioning**: Children are placed one after another along the main axis.
*   **Gravity Application**: After all children are measured, `LinearLayout` adjusts their positions based on the `gravity` setting (e.g., pushing all children to the bottom of a vertical layout).

### 3. Dividers
*   Supports drawing `Drawable` dividers between children (`setShowDividers`).
*   Logic handles `SHOW_DIVIDER_BEGINNING`, `MIDDLE`, and `END`.

### 4. Baseline Alignment
*   In horizontal mode, it can align children based on their text baselines (`setBaselineAligned`), which is essential for making rows of labels and inputs look professionally aligned.

## Data Model
*   **`LinearLayout.LayoutParams`**: Extends `MarginLayoutParams`. Adds the `weight` (float) and `gravity` (int) fields.

## Java-to-C++ Translation Guide
*   **Dual-Pass Measurement**: C++ implementation MUST follow the two-pass measurement logic:
    1.  Pass 1: Collect total fixed size and total weight.
    2.  Pass 2: Distribute remaining space and perform final measurement of weighted children.
*   **Gravity Math**: Use bitwise masking to extract horizontal and vertical gravity components and apply offsets to the child frames.

## Implementation Risks
*   **Nested Weights**: Placing a `LinearLayout` with weights inside another `LinearLayout` with weights causes exponential measurement complexity ($O(2^n)$) and should be avoided.
*   **RTL Support**: Horizontal positioning must correctly flip indices and offsets when `layoutDirection` is `RTL`.
*   **Rounding Errors**: Distributed weight pixels must be rounded carefully to avoid one-pixel gaps between children.
