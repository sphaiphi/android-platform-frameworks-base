# ActionMenuView - Reverse Engineering Documentation

## Executive Summary
`ActionMenuView` is the container view (a `LinearLayout` subclass) that displays the action items managed by `ActionMenuPresenter`. It lays out action buttons horizontally and provides the anchor for the overflow menu. It implements `MenuBuilder.ItemInvoker` and `MenuView`.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `ActionMenuView`.
*   **Role**: Container for Action Bar / Toolbar items.
*   **Key Dependencies**:
    *   `ActionMenuPresenter`: Controls the logic.
    *   `MenuBuilder`: The data source.

## Detailed Functionality

### 1. Measurement (`onMeasure`)
*   **Cell-based Layout**: Unlike standard linear layouts, `ActionMenuView` often uses a cell-based approach to align items (e.g., on tablets or specific toolbar configurations).
*   **Overflow Handling**: Detects if the overflow button is present and reserves space for it.
*   **Expansion**: Logic to distribute extra space among items if `expandedActionViewsExclusive` is not set.

### 2. Layout (`onLayout`)
*   Standard horizontal positioning.
*   Supports RTL (Right-to-Left) layouts.

### 3. Interaction
*   `invokeItem`: Delegates menu item invocation to the `MenuBuilder`.
*   `generateLayoutParams`: Uses custom `LayoutParams` (`ActionMenuView.LayoutParams`) which carry extra info like `isOverflowButton` or `cellsUsed`.

## Java-to-C++ Translation Guide
*   **Flexibility**: The measurement logic handles both "exact" sizing (cells) and standard flow. C++ layout system must handle these dual modes if faithful reproduction is required.
*   **Params**: `LayoutParams` needs to store the `isOverflowButton` boolean to identify the anchor during layout.

## Implementation Risks
*   **Complexity**: The `onMeasure` method is dense, handling various edge cases for spacing, dividers, and cell distribution. Simplification might be possible if only specific Toolbar use-cases are needed.
