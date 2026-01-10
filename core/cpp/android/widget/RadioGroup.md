# RadioGroup - Reverse Engineering Documentation

## Executive Summary
`RadioGroup` is a `LinearLayout` that manages a set of `RadioButton`s. It ensures only one button is checked at a time.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `RadioGroup`.
*   **Role**: Exclusive Scope.

## Detailed Functionality
*   **Tracking**: Uses `PassThroughHierarchyChangeListener` to detect when `RadioButton`s are added or removed.
*   **Listeners**: Sets a `OnCheckedChangeListener` on all children. When a child is checked, the group sets the previously checked child to unchecked.
*   **State**: Stores `mCheckedId`.

## Java-to-C++ Translation Guide
*   **Hierarchy Listener**: Crucial to automatically hook up buttons added via XML or code.
*   **Recursion Prevention**: Uses a flag (`mProtectFromCheckedChange`) to prevent infinite loops when updating child states.

## Implementation Risks
*   **Dynamic Views**: Handling views added/removed dynamically.
