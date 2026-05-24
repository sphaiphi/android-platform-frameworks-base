# ChangeScroll - Reverse Engineering Documentation

## Executive Summary
`ChangeScroll` animates the scroll position (`scrollX`, `scrollY`) of a View.

## Key Algorithms
-   **`captureValues`**: Records `getScrollX()` and `getScrollY()`.
-   **`createAnimator`**: Creates `ObjectAnimator` for `scrollX` and `scrollY` if values differ. Uses `TransitionUtils.mergeAnimators` if both change.

## Java-to-C++ Translation Guide
-   **Scroll Offsets**: Maps to animating content offset properties in a UI toolkit.
