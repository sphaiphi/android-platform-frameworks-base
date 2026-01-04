# ScrollView - Reverse Engineering Documentation

## Executive Summary
`ScrollView` is a `FrameLayout` that allows a single child view to be taller than the physical screen. It provides vertical scrolling logic, handling touch events, flings, and nested scrolling.

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `ScrollView`.
*   **Key Components**:
    *   `OverScroller`: Handles physics (fling, springback).
    *   `EdgeEffect`: Top and bottom overscroll visuals ("glow").
    *   `VelocityTracker`: Tracks finger speed for flings.

## Detailed Functionality

### 1. Input Handling (`onTouchEvent`)
*   **Drag**: Detects vertical drags (`ACTION_MOVE`) considering `mTouchSlop`.
*   **Fling**: On `ACTION_UP`, computes velocity and calls `fling()`.
*   **Overscroll**: Supports pulling beyond boundaries (`overScrollBy`), triggering `EdgeEffect`.

### 2. Measurement & Layout
*   **Measure**:
    *   Standard `FrameLayout` measurement.
    *   **`fillViewport`**: If true and the child is shorter than the scroll view, forces the child to expand to fill the height.
*   **Layout**: Standard layout. Clamps `mScrollY` if the content shrinks.

### 3. Scrolling Logic
*   **`computeScroll`**: Called by the drawing system. Advances the `OverScroller`. If the scroller moves, calls `scrollTo`.
*   **`scrollTo`**: Clamps values to valid ranges (0 to contentHeight - viewHeight).

### 4. Nested Scrolling
*   Implements `NestedScrollingParent` and `NestedScrollingChild` patterns.
*   Dispatches pre-scroll and scroll events to parents (allowing coordination with `CoordinatorLayout`).

### 5. Keyboard & Accessibility
*   Handles D-pad arrows, PageUp/Down, Home/End, Spacebar.
*   Animates scrolling (`smoothScrollTo`).

## Java-to-C++ Translation Guide
*   **Touch Handling**: The state machine in `onTouchEvent` (down, move, up, cancel, pointer_up) is complex and critical.
*   **Physics**: Relies heavily on `OverScroller` matching the platform feel.
*   **Edge Effects**: Integration with `EdgeEffect` for visual feedback.

## Implementation Risks
*   **Nested Scrolling**: This is the hardest part to get right. It involves a handshake protocol with parent and child views.
*   **Focus**: `ScrollView` has logic to automatically scroll to a child that receives focus (`requestChildFocus`, `scrollToDescendant`).
