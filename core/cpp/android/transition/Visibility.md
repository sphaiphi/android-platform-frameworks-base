# Visibility - Reverse Engineering Documentation

## Executive Summary
Abstract subclass of `Transition` specifically for animations triggering on visibility changes (Visible/Invisible/Gone) or when views are added/removed.

## Key Algorithms
-   **`getVisibilityChangeInfo`**: Compares start/end visibility and parentage to determine if an animation is needed (Appear vs Disappear).
-   **`createAnimator`**:
    -   Calls `onAppear` or `onDisappear`.
-   **`onDisappear` (Default)**:
    -   Handles logic for views removed from hierarchy.
    -   Adds them to `ViewOverlay` if necessary so they can be animated out even after being removed from the layout tree.
    -   Handles "View to Keep" logic if simply changing visibility flags.

## API Reference
-   **`onAppear(...)`**: Abstract-ish (default returns null).
-   **`onDisappear(...)`**: Abstract-ish.

## Java-to-C++ Translation Guide
-   **Lifecycle**: Managing views that are "technically removed" but "visually present" (overlay) is the core complexity here.
