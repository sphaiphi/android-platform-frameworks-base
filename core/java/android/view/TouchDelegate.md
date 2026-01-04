# TouchDelegate - Reverse Engineering Documentation

## Executive Summary
`TouchDelegate` is a helper class that allows a `View` to have a larger (or different) touch area than its actual physical bounds. It is used by an ancestor view to redirect touch events to a "delegate" child view when the touch occurs within a specified "delegate" rectangle.

## Architecture Overview
*   **Role**: Touch target expansion utility.
*   **Mechanism**: Intercepts `MotionEvent`s in the parent view and forwards them to the child view after modifying their coordinates to be centered on the child.

## Detailed Functionality

### 1. Hit Testing
*   **`mBounds`**: The target area in parent coordinates.
*   **`mSlopBounds`**: An inflated version of the bounds used to track gestures once they have started (providing "sticky" touch behavior).

### 2. Event Forwarding
*   **`onTouchEvent()`**: Checks if the initial `ACTION_DOWN` is within `mBounds`. If so, it redirects all subsequent events in the gesture to the delegate view.
*   **Coordinate Remapping**: When a hit occurs, it offsets the event location to the center of the delegate view to ensure standard click listeners are triggered correctly.

### 3. Accessibility
*   **`getTouchDelegateInfo()`**: Provides a mapping of regions to delegated views, allowing screen readers to correctly identify larger touch targets.

## Java-to-C++ Translation Guide
*   **Pattern**: Delegate Pattern / Proxy.
*   **Logic**: Primarily involves `Rect::contains` and `MotionEvent::setLocation`.

## Implementation Risks
*   **Multiple Delegates**: A single parent can only have one `TouchDelegate` at a time.
*   **Coordinate Context**: The `mBounds` rectangle MUST be in the local coordinate system of the parent view where the delegate is registered.
