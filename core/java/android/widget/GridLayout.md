# GridLayout - Reverse Engineering Documentation

## Executive Summary
`GridLayout` is a layout manager that places children in a rectangular grid. Unlike `TableLayout`, it does not enforce a rigid row/column structure; children can span multiple rows/columns and be placed arbitrarily. It uses a constraint-solving algorithm to determine row heights and column widths.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `GridLayout`.
*   **Key Internal Class**: `Axis` (Horizontal and Vertical).
*   **Algorithm**: Bellman-Ford algorithm (modified) to solve linear constraints.

## Detailed Functionality

### 1. Specs
*   **`RowSpec` / `ColumnSpec`**: Define the span (start, size) and alignment for a child.
*   **Default Placement**: If indices are undefined, it automatically places children in the next available cell.

### 2. Constraint Solving (`Axis`)
*   Modeled as a graph problem.
*   **Nodes**: Grid lines.
*   **Arcs**: Constraints (e.g., "column 1 must be at least 50px wide", "width of col 1 + col 2 must be > child width").
*   **Solution**: Finds the minimum locations for grid lines that satisfy all constraints.

### 3. Measurement & Layout
*   **Measure**: Collects all child constraints, runs the solver to find total width/height.
*   **Layout**: Uses the solved grid line locations to position children. Handles gravity/alignment within cells.

## Java-to-C++ Translation Guide
*   **Graph Algorithm**: Requires a robust implementation of the constraint solver. The Java implementation uses a topological sort + Bellman-Ford approach.
*   **Data Structures**: `PackedMap`, `Interval`, `Arc` classes are needed to manage the graph efficiently.

## Implementation Risks
*   **Performance**: Solving the graph can be expensive ($O(N^2)$ or better depending on implementation) for complex grids.
*   **Complexity**: This is one of the most mathematically complex layouts in Android.
