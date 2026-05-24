# AccessibilityInteractionController - Reverse Engineering Documentation

## Executive Summary
`AccessibilityInteractionController` is the primary engine for processing accessibility-related queries and actions within a specific window. It acts as a dispatcher between the system accessibility services (via `AccessibilityManagerService`) and the `View` hierarchy. It handles finding nodes by ID, text, or focus, and executing accessibility actions like clicking or scrolling.

## Architecture Overview
*   **Role**: Per-window accessibility dispatcher.
*   **Threading**: Operations initiated from the binder thread (ClientThread) are scheduled onto the UI thread (UiThread) for safe interaction with the View tree.
*   **Prefetching**: Includes an optimization strategy (`AccessibilityNodePrefetcher`) to fetch a batch of related nodes (ancestors, siblings, descendants) in a single IPC call to reduce latency.

## Detailed Functionality

### 1. Node Discovery
*   **`findAccessibilityNodeInfoByAccessibilityId...`**: Locates a specific node.
*   **`findAccessibilityNodeInfosByViewId...`**: Finds views matching a specific resource ID string.
*   **`findAccessibilityNodeInfosByText...`**: Performs text-based search across the hierarchy.

### 2. Focus and Search
*   **`findFocus...`**: Locates the currently focused node (either input focus or accessibility focus).
*   **`focusSearch...`**: Finds the next focusable node in a given direction (Up, Down, Left, Right).

### 3. Action Execution
*   **`performAccessibilityAction...`**: Executes standard actions (Click, Long Click, Scroll) or custom actions on a target node.

### 4. Prefetching Strategy
*   Iteratively explores the tree based on flags (`FLAG_PREFETCH_ANCESTORS`, `FLAG_PREFETCH_SIBLINGS`, `FLAG_PREFETCH_DESCENDANTS`) to provide context to the accessibility service without multiple round-trips.

## Java-to-C++ Translation Guide
*   **Message Loop**: Use `ALooper` or `android::Handler` to schedule tasks from Binder threads to the UI thread.
*   **Node ID Mapping**: Use `AccessibilityNodeIdManager` (or a native equivalent) to map 64-bit accessibility IDs back to `View` instances.
*   **Matrix Transformations**: Use `android::Matrix` to handle screen-to-window coordinate adjustments, especially for embedded hierarchies.

## Implementation Risks
*   **UI Thread Blocking**: Since all interactions run on the UI thread, heavy queries or complex trees can cause jank or trigger ANRs.
*   **Consistency**: The controller must ensure the node tree is consistent (no duplicates, correct parent-child links) to prevent accessibility services from crashing or behaving erratically.
