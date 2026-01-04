# AppTransitionAnimationSpec - Reverse Engineering Documentation

## Executive Summary
`AppTransitionAnimationSpec` is a data structure used to describe how a specific task window should be animated during an app transition (e.g., when opening or closing a task). It primarily maps a task ID to a source buffer (usually a thumbnail) and a target destination rectangle.

## Data Model
*   **`taskId`**: `int` - The identifier of the task this spec applies to.
*   **`buffer`**: `HardwareBuffer` - A snapshot of the task's content to be used as an animation leash.
*   **`rect`**: `Rect` - The target coordinates on the screen where the task will be positioned.

## Detailed Functionality
*   **Parcelable**: This class is designed for IPC, allowing `WindowManagerService` to receive animation specs from a client (like the Launcher).
*   **Snapshot Logic**: Used in "Thumbnail" transitions where the app appears to grow out of an icon.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Map to a C++ `struct` or `class` that wraps `AHardwareBuffer`.
*   **Parceling**: Ensure the C++ serialization logic matches the Java fields: `int`, `Rect`, then `HardwareBuffer`.

## Implementation Risks
*   **Buffer Lifecycle**: The `HardwareBuffer` must be correctly released in both processes to avoid memory leaks.
*   **Stale Specs**: Animation specs become invalid if the task layout changes significantly before the transition starts.
