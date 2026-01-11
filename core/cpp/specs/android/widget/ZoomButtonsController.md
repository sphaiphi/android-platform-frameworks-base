# ZoomButtonsController - Reverse Engineering Documentation

## Executive Summary
`ZoomButtonsController` manages a floating window containing zoom controls (+/- buttons) that appears on top of an owner view. It handles auto-dismissal and positioning.

## Architecture Overview
*   **Status**: Deprecated.
*   **Role**: Floating UI Manager.

## Detailed Functionality
*   **Window**: Adds a `FrameLayout` containing `ZoomControls` to the `WindowManager`.
*   **Positioning**: Aligns the window to the bottom of the owner view.
*   **Touch Stealing**: Can register itself as a touch listener on the owner view to show controls on touch.

## Java-to-C++ Translation Guide
*   **Overlay**: Floating UI logic.

## Implementation Risks
*   **Window Leaks**: Must detach from WindowManager.
