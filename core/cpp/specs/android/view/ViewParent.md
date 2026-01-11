# ViewParent - Reverse Engineering Documentation

## Executive Summary
`ViewParent` defines the responsibilities of a class that can act as a parent to a `View`. While `ViewGroup` is the most common implementation, `ViewRootImpl` also implements this interface to act as the top-level parent. It defines the protocol for child-to-parent communication (invalidation, layout requests, focus search).

## Architecture Overview
*   **Role**: Child-to-Parent contract.
*   **Key Interface for**: Layout propagation and Event bubbling.

## Detailed Functionality

### 1. Invalidation & Layout
*   **`requestLayout()`**: Propagates a layout request up the tree until it reaches the root.
*   **`onDescendantInvalidated()`**: Notifies the parent that a child needs to redraw.

### 2. Focus & Interaction
*   **`requestChildFocus(child, focused)`**: Notifies the parent that a descendant has taken focus.
*   **`focusSearch(v, direction)`**: asks the parent to find the next focusable view in a specific direction.
*   **`requestDisallowInterceptTouchEvent(boolean)`**: Tells the parent (and its ancestors) not to intercept touch events (crucial for scrolling interactions).

### 3. Geometry
*   **`getChildVisibleRect()`**: Calculates the visible portion of a child view, clipping against the parent's bounds.

## Java-to-C++ Translation Guide
*   **Virtual Base Class**: `ViewParent` should be a pure virtual class.
*   **Traversal**: Many methods (`requestLayout`, `getParent`) rely on walking up the tree; ensure the parent pointer in `View` is accessible and safe.

## Implementation Risks
*   **Recursion Depth**: In extremely deep hierarchies, recursive calls up the `ViewParent` chain can cause stack overflow. Iterative implementations are preferred where possible.
