# ViewTreeObserver - Reverse Engineering Documentation

## Executive Summary
`ViewTreeObserver` is a registry for global events happening within a view tree. It allows listeners to be notified of layout passes, pre-draw events, touch mode changes, and scroll updates. It is attached to the `View` hierarchy and managed by the `ViewRootImpl`.

## Architecture Overview
*   **Role**: Global event broadcaster.
*   **Lifecycle**: Objects are "alive" or "dead". When a view detaches, its observer might be merged into another one or killed.
*   **Listeners**: Uses `CopyOnWriteArrayList` or `CopyOnWriteArray` to safely handle listener modifications during dispatch.

## Detailed Functionality

### 1. Key Listeners
*   **`OnGlobalLayoutListener`**: Fired after the layout pass is complete.
*   **`OnPreDrawListener`**: Fired before drawing starts. Returning `false` cancels the draw (useful for animations needing one more layout pass).
*   **`OnScrollChangedListener`**: Fired when any view in the tree scrolls.
*   **`OnTouchModeChangeListener`**: Fired when the user switches between touch and key navigation.

### 2. Merge Logic
*   **`merge(ViewTreeObserver)`**: When views are attached to a window, their temporary, local `ViewTreeObserver` is merged into the window's global observer.

## Java-to-C++ Translation Guide
*   **Observer Pattern**: Standard C++ observer pattern using `std::vector<std::function<void()>>`.
*   **Safety**: Use `std::weak_ptr` for listeners to avoid dangling pointers if the listener object is destroyed before the observer.

## Implementation Risks
*   **Performance**: `OnScrollChanged` and `OnPreDraw` fire very frequently (potentially every frame). Listeners must be lightweight.
*   **Infinite Loops**: Modifying layout properties inside `OnGlobalLayoutListener` without removing the listener will cause an infinite layout loop.
