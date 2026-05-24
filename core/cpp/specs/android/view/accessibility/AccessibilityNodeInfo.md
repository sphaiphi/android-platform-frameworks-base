# AccessibilityNodeInfo - Reverse Engineering Documentation

## Executive Summary
A snapshot of a View's state for accessibility purposes. It is the primary data structure exchanged between apps and accessibility services. It represents a node in the logical accessibility tree.

## Data Model
*   **IDs**: `mSourceNodeId`, `mWindowId`, `mParentNodeId`.
*   **Properties**: Bounds (`Rect`), Text, ContentDescription, ClassName, PackageName.
*   **Flags**: Boolean properties packed into `mBooleanProperties` (focusable, clickable, etc.).
*   **Actions**: List of `AccessibilityAction` supported by the node.
*   **Children**: `LongArray` of child node IDs (virtual or real).

## Key Concepts
*   **Virtual Nodes**: Can represent a virtual view (e.g., a drawn element inside a Canvas) using `virtualDescendantId`.
*   **Sealing**: Can be "sealed" (immutable) to prevent modification after being dispatched.
*   **Prefetching**: Flags to control prefetching strategies.

## Java-to-C++ Translation Guide
*   **Parcelable**: Complex parceling logic.
*   **Bit Operations**: Heavy use of bitmasks for flags and IDs (`makeNodeId`, `getVirtualDescendantId`).
