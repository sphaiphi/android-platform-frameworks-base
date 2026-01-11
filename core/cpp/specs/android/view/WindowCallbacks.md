# WindowCallbacks - Reverse Engineering Documentation

## Executive Summary
`WindowCallbacks` is an internal interface used by `ViewRootImpl` to communicate window-level configuration and resizing events to interested components (like the system navigation bar or specialized layouts). it is primarily used during interactive resizing (e.g., drag-resizing a window).

## Architecture Overview
*   **Role**: Window configuration event listener.
*   **Usage**: Registered with `ViewRootImpl`.

## Detailed Functionality
*   **`onWindowSizeIsChanging()`**: Called before the layout pass when a user is resizing the window.
*   **`onContentDrawn()`**: Triggered after a frame is rendered, providing the final dimensions and offsets.
*   **`onPostDraw()`**: Allows a component to perform raw rendering on top of the entire window after all other views have finished drawing.

## Java-to-C++ Translation Guide
*   **Interface**: Define as a virtual interface in C++.
*   **Integration**: Implement in native components that need to react to real-time window geometry changes.

## Implementation Risks
*   **Performance**: `onWindowSizeIsChanging` must complete within ~4ms to avoid stutter during interactive resizing.
