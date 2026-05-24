# HorizontalScrollView - Reverse Engineering Documentation

## Executive Summary
`HorizontalScrollView` is a `FrameLayout` that allows its content to be larger than its physical width, enabling horizontal scrolling. It is the horizontal counterpart to `ScrollView`.

## Architecture Overview
*   **Inheritance**: `FrameLayout` -> `HorizontalScrollView`.
*   **Role**: Scrolling Container.

## Detailed Functionality
*   **Measurement**: Measures child with `UNSPECIFIED` width mode (unbounded) to let it grow as wide as needed.
*   **Touch Handling**: Uses `VelocityTracker` and `OverScroller` to handle flings.
*   **Fill Viewport**: If `fillViewport` is true, forces the child to be at least as wide as the parent.

## Java-to-C++ Translation Guide
*   **Scrolling Logic**: Replicate `ScrollView` logic but on the X-axis.
*   **Input**: Handle touch events, pass to `OverScroller`.

## Implementation Risks
*   **Nested Scrolling**: Handling touch interception correctly when placed inside other scrollable containers (like `ViewPager` or vertical `ScrollView`).
