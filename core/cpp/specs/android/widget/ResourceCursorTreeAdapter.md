# ResourceCursorTreeAdapter - Reverse Engineering Documentation

## Executive Summary
`ResourceCursorTreeAdapter` is a `CursorTreeAdapter` that inflates group and child views from XML resources.

## Architecture Overview
*   **Inheritance**: `CursorTreeAdapter` -> `ResourceCursorTreeAdapter`.

## Detailed Functionality
*   **Layouts**: Stores resource IDs for collapsed group, expanded group, child, and last child.
*   **Inflation**: Inflates the appropriate resource in `newGroupView` and `newChildView`.

## Java-to-C++ Translation Guide
*   **Simplified**: Basic wrapper.

## Implementation Risks
*   None.
