# SubMenu - Reverse Engineering Documentation

## Executive Summary
`SubMenu` is an extension of the `Menu` interface representing a nested menu. It adds functionality to manage its own header and provides a link back to the `MenuItem` that serves as its parent in the primary menu.

## Architecture Overview
*   **Role**: Hierarchical menu container.
*   **Constraint**: Android typically supports only one level of nesting (submenus cannot contain further submenus).

## Detailed Functionality
*   **`getItem()`**: Returns the `MenuItem` that triggers this submenu.
*   **Header Control**: Like `ContextMenu`, it supports `setHeaderTitle`, `setHeaderIcon`, and `setHeaderView`.
*   **Icon Management**: `setIcon()` allows changing the icon of the parent item directly from the submenu object.

## Java-to-C++ Translation Guide
*   **Hierarchy**: Implement as a child class of `Menu`.
*   **Recursive Cleanup**: Ensure that when a submenu is cleared, its parent item is notified.

## Implementation Risks
*   **Infinite Recursion**: Guard against accidental multi-level nesting if the native UI toolkit's limitation matches Android's.
