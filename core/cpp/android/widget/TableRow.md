# TableRow - Reverse Engineering Documentation

## Executive Summary
`TableRow` is a `LinearLayout` (Horizontal) designed to be used inside `TableLayout`. It aligns its children based on column widths provided by the parent `TableLayout`.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `TableRow`.
*   **Role**: Row container.

## Detailed Functionality

### 1. Virtual Children
*   Supports `layout_span` and `layout_column`.
*   **`mapIndexAndColumns`**: Maps child views to column indices (handling spans and skipped columns).

### 2. Measurement
*   **`measureChildBeforeLayout`**:
    *   Uses `mConstrainedColumnWidths` provided by parent.
    *   Forces child width to match the column width (or sum of spanned columns).
    *   Handles `gravity` to position child within the cell.

### 3. LayoutParams
*   Adds `column` and `span` attributes.

## Java-to-C++ Translation Guide
*   **Coupling**: Highly coupled with `TableLayout`.
*   **Virtual Indexing**: Logic to handle "virtual" children (empty cells) vs actual child views.

## Implementation Risks
*   None if `TableLayout` logic is correct.
