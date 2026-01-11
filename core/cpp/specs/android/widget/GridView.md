# GridView - Reverse Engineering Documentation

## Executive Summary
`GridView` is a `AbsListView` implementation that displays items in a 2D scrolling grid.

## Architecture Overview
*   **Inheritance**: `AbsListView` -> `GridView`.
*   **Role**: Grid-based collection view.

## Detailed Functionality

### 1. Layout (`layoutChildren`)
*   **`fillUp` / `fillDown`**: Similar to `ListView`, but fills a *row* at a time instead of a single view.
*   **`makeRow`**: Creates/reuses `mNumColumns` views, positions them horizontally, and returns the row height (max of child heights).

### 2. Column Calculation
*   **`AUTO_FIT`**: Calculates number of columns based on `columnWidth` and available space.
*   **Stretch Modes**:
    *   `STRETCH_COLUMN_WIDTH`: Expands columns.
    *   `STRETCH_SPACING`: Expands space between columns.
    *   `STRETCH_SPACING_UNIFORM`: Uniform spacing.

### 3. Selection
*   Navigation moves focus spatially (up/down moves by `numColumns`, left/right by 1).

## Java-to-C++ Translation Guide
*   **Grid Logic**: Extend the `AbsListView` implementation. Replace the linear fill logic with row-based fill logic.

## Implementation Risks
*   **Row Height**: All items in a row usually need to have the same height for consistent scrolling, or the logic gets complicated. `GridView` typically assumes the row height is the max of the items in that row.
