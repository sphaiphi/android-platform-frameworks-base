# RelativeLayout - Reverse Engineering Documentation

## Executive Summary
`RelativeLayout` is a powerful layout container that enables complex UI designs by positioning children relative to each other or to the parent container. It uses a constraint-based system (Rules) to solve for the final positions of all children, eliminating the need for deeply nested hierarchies.

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `RelativeLayout`.
*   **Dependency Graph**: Internally maintains a `DependencyGraph` to determine the order in which children must be measured. If View A is positioned relative to View B, B must be measured first.
*   **Two-Pass Measurement**:
    1.  **Horizontal Pass**: Solves for `left` and `right` coordinates for all children.
    2.  **Vertical Pass**: Solves for `top` and `bottom` coordinates.

## Detailed Functionality

### 1. The Rule System ("Verbs")
Children define their position using "rules" in `LayoutParams`:
*   **Relative to Siblings**: `LEFT_OF`, `RIGHT_OF`, `ABOVE`, `BELOW`, `ALIGN_LEFT`, etc.
*   **Relative to Parent**: `ALIGN_PARENT_TOP`, `CENTER_IN_PARENT`, `CENTER_HORIZONTAL`, etc.
*   **RTL Aware**: `START_OF`, `END_OF`, `ALIGN_PARENT_START`.

### 2. Dependency Resolution
*   `sortChildren()`: Performs a topological sort of the children based on their dependencies.
*   **Circular Dependencies**: The layout will fail or produce incorrect results if circular dependencies are detected (e.g., A is below B, and B is below A).

### 3. Measurement Logic
*   For each axis (horizontal/vertical), the layout iterates through the sorted children.
*   It calculates the available space for each child based on its active rules.
*   `resolveSize()`: Reconciles the child's desired size with the calculated constraints.

### 4. Gravity Application
*   Once all children are positioned, the global `gravity` of the `RelativeLayout` is applied by shifting the entire block of children as a single unit within the parent bounds.

## Data Model
*   **`RelativeLayout.LayoutParams`**: Extends `MarginLayoutParams`. Contains an array `mRules` (int[22]) representing the active constraints for the view.

## Java-to-C++ Translation Guide
*   **Graph Sorting**: Use a standard topological sort algorithm (Kahn's or DFS-based) to resolve view dependencies.
*   **Constraint Solver**: Implement a iterative solver that calculates edge coordinates (`mLeft`, `mTop`, etc.) axis-by-axis.
*   **Memory**: The `DependencyGraph` and sorted lists should be cached and only recomputed when `requestLayout()` is called (tracked via `mDirtyHierarchy`).

## Implementation Risks
*   **Performance**: Complexity is $O(N)$ where $N$ is the number of children, but the constant factor is high due to graph management and dual passes.
*   **RTL Complexity**: Correctly mapping `START`/`END` rules based on the `layoutDirection` requires careful state management during the horizontal pass.
*   **MeasureSpec Overflow**: Historical "broken" behavior for large specifications must be emulated for apps with low `targetSdkVersion`.
