# ViewAnimator - Reverse Engineering Documentation

## Executive Summary
`ViewAnimator` is a `FrameLayout` that manages a list of child views and displays only one at a time. It supports animations when switching between views.

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `ViewAnimator`.
*   **Key State**: `mWhichChild` (index of currently shown child).

## Detailed Functionality
*   **`setDisplayedChild`**:
    *   Hides the previously shown child.
    *   Shows the new child.
    *   Starts `mInAnimation` on the new child and `mOutAnimation` on the old child.
*   **`showNext` / `showPrevious`**: Wraps around indices.

## Java-to-C++ Translation Guide
*   **Visibility**: Relies on `setVisibility(VISIBLE/GONE)`.
*   **Animation**: Triggers view animations.

## Implementation Risks
*   None.
