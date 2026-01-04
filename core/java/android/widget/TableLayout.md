# TableLayout - Reverse Engineering Documentation

## Executive Summary
`TableLayout` extends `LinearLayout` (Vertical) to arrange children (`TableRow`s) into rows and columns. It enforces column alignment across rows.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `TableLayout`.
*   **Children**: Usually `TableRow`, but can be any View (which spans all columns).

## Detailed Functionality

### 1. Column Measurement (`findLargestCells`)
*   Iterates *all* rows first.
*   Finds the maximum width for each column index across all rows.
*   Stores these in `mMaxWidths`.

### 2. Sizing (`shrinkAndStretchColumns`)
*   If rows exceed available width:
    *   **Shrinkable**: Reduces width of shrinkable columns.
*   If rows are narrower than available width:
    *   **Stretchable**: Distributes extra space to stretchable columns.

### 3. Pass-Through Listener
*   Uses `PassThroughHierarchyChangeListener` to track when rows are added and apply column collapse settings.

## Java-to-C++ Translation Guide
*   **Two-Pass Measure**: `TableLayout` acts as a solver. It measures children to find column requirements, resolves them, then forces children to re-measure with fixed column widths.
*   **Column Map**: Needs to track column indices, spans, and collapse states.

## Implementation Risks
*   **Performance**: Deep nesting of TableLayouts is expensive due to the multi-pass measurement.
