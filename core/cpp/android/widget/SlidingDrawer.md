# SlidingDrawer - Reverse Engineering Documentation

## Executive Summary
`SlidingDrawer` is a deprecated widget that hides content off-screen and allows a user to drag a "handle" to reveal it. It acts as a sliding overlay (drawer).

## Architecture Overview
*   **Inheritance**: `ViewGroup` -> `SlidingDrawer`.
*   **Status**: Deprecated.
*   **Components**:
    *   `mHandle`: The view the user touches.
    *   `mContent`: The hidden view.

## Detailed Functionality

### 1. Layout
*   Positions the handle and content relative to the parent bounds.
*   **Vertical**: Handle is at top/bottom. Content follows it.
*   **Horizontal**: Handle is left/right.

### 2. Touch Handling
*   **Intercept**: Intercepts touches on the handle.
*   **Drag**: Moves the handle and content view in `onTouchEvent` (`moveHandle`).
*   **Fling**: Uses `VelocityTracker` to detect flings and animate to open/closed state.

### 3. Animation
*   Custom manual animation loop (`mSlidingRunnable`) instead of `ObjectAnimator` (because it's old code). Updates position and calls `invalidate()`.

## Java-to-C++ Translation Guide
*   **Legacy**: Implement only if supporting legacy behavior. Modern equivalents use `BottomSheetBehavior` or `DrawerLayout`.
*   **Logic**: Standard drag-and-drop physics.

## Implementation Risks
*   **Performance**: The legacy implementation used `DrawingCache` (bitmaps) during animation for performance, which is now obsolete/inefficient compared to hardware layers.
