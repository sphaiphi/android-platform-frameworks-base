# SimpleCursorTreeAdapter - Reverse Engineering Documentation

## Executive Summary
`SimpleCursorTreeAdapter` extends `ResourceCursorTreeAdapter` to provide easy mapping of cursor columns to views for both Groups and Children in an `ExpandableListView`.

## Architecture Overview
*   **Inheritance**: `ResourceCursorTreeAdapter` -> `SimpleCursorTreeAdapter`.

## Detailed Functionality
*   **Mapping**: Maintains separate `from`/`to` arrays for Groups (`mGroupFrom`, `mGroupTo`) and Children (`mChildFrom`, `mChildTo`).
*   **Binding**: Implements `bindGroupView` and `bindChildView` using the same logic as `SimpleCursorAdapter`.

## Java-to-C++ Translation Guide
*   **Logic**: Combination of `ResourceCursorTreeAdapter` lifecycle + `SimpleCursorAdapter` binding logic.

## Implementation Risks
*   None.
