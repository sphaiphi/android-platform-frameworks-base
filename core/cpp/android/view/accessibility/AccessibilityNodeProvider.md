# AccessibilityNodeProvider - Reverse Engineering Documentation

## Executive Summary
Abstract class (contract) for views that provide a virtual view hierarchy (e.g., WebViews, custom drawing views). It allows a View to expose a tree of `AccessibilityNodeInfo`s that doesn't match the actual View hierarchy.

## Key Methods
*   **`createAccessibilityNodeInfo(int virtualViewId)`**: Returns the node info for a virtual ID.
*   **`performAction`**: Performs accessibility actions on virtual nodes.
*   **`findAccessibilityNodeInfosByText`**: Search functionality.

## Java-to-C++ Translation Guide
*   **Virtual Base Class**: Maps to a C++ abstract base class/interface.
