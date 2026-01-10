# AccessibilityRecord - Reverse Engineering Documentation

## Executive Summary
The base class for `AccessibilityEvent`. It holds the core state information (scroll position, item count, selection, etc.) associated with a UI change. Events contain records (though typically just one).

## Data Model
*   **Source**: `mSourceNodeId`, `mSourceWindowId`.
*   **State**: `mChecked`, `mEnabled`, `mScrollX/Y`, `mFromIndex`, `mItemCount`.
*   **Text**: `mText` (List of CharSequences).

## Java-to-C++ Translation Guide
*   **Inheritance**: `AccessibilityEvent` inherits from this.
*   **Object Pooling**: Has deprecated `obtain`/`recycle` methods (historical artifact).
