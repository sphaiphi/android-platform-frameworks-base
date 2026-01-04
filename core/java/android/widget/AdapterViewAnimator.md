# AdapterViewAnimator - Reverse Engineering Documentation

## Executive Summary
`AdapterViewAnimator` is a base class for `AdapterView`s that perform animations when switching between views, such as `StackView` and `AdapterViewFlipper`. It manages a window of active views, handles recycling via an `Adapter` or `RemoteViewsAdapter`, and orchestrates in/out animations.

## Architecture Overview
*   **Inheritance**: `AdapterView` -> `AdapterViewAnimator`.
*   **Key Components**:
    *   `ViewAndMetaData`: Internal class holding the view and its adapter position/id.
    *   `mViewsMap`: HashMap storing currently active views.
    *   `ObjectAnimator`: `mInAnimation` and `mOutAnimation` for transitions.

## Detailed Functionality

### 1. View Window Management
*   Maintains a "window" of active views around the current index (`mWhichChild`).
*   **`showOnly(int childIndex, boolean animate)`**: The core logic.
    *   Calculates the new range of visible indices (handling looping if enabled).
    *   Removes views falling out of range (adds to `mPreviousViews` for animation out).
    *   Adds new views entering the range (requests from Adapter).
    *   Applies transforms and animations.

### 2. Animation
*   Uses `ObjectAnimator` for entering and exiting views.
*   **`transformViewForTransition`**: Overrideable method to customize how views behave during the transition (e.g., StackView's depth effect).

### 3. RemoteViews Support
*   Implements `RemoteAdapterConnectionCallback` to handle async connection to `RemoteViewsService` for widgets.

## Java-to-C++ Translation Guide
*   **View Map**: `std::map<int, ViewAndMetaData>` or `std::unordered_map`.
*   **Animator**: Requires a property animation system.
*   **Modulo Arithmetic**: Java's `%` operator can return negative values. Helper `modulo(pos, size)` ensures positive indices for looping.

## Implementation Risks
*   **Adapter Lifecycle**: Handling async loading of RemoteViews while the user is interacting/scrolling.
*   **Looping Logic**: Correctly calculating ranges when `mLoopViews` is true and the window wraps around the adapter count.
