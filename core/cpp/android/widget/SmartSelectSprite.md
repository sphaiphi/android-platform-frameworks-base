# SmartSelectSprite - Reverse Engineering Documentation

## Executive Summary
`SmartSelectSprite` is a graphics utility class used by `SelectionActionModeHelper` to render the "smart selection" expansion animation. It draws a rounded rectangle (or polygon) that expands from the user's touch point to fill the selected text bounds.

## Architecture Overview
*   **Role**: Animation/Rendering Helper.
*   **Not a View**: It manages a `ShapeDrawable` and draws onto a Canvas provided by the `TextView`.

## Detailed Functionality

### 1. Shape Generation
*   **`RoundedRectangleShape`**: A custom shape representing a selection highlight on a single line.
*   **`RectangleList`**: Combines multiple rectangles (for multi-line selections) into a single path using `Path.Op.UNION`.

### 2. Animation
*   **Input**: Takes a list of destination rectangles (the final selection bounds).
*   **Animator**: Uses `ObjectAnimator` to animate the `rightBoundary` and `leftBoundary` properties of the `RectangleList`.
*   **Effect**: The shape starts "collapsed" at the touch point and expands outwards to fill the destination bounds.

## Java-to-C++ Translation Guide
*   **Path Ops**: Requires 2D path boolean operations (Union) to merge selection rectangles on different lines.
*   **Animation**: Interpolation logic (`fast_out_slow_in`).

## Implementation Risks
*   **Canvas Clip**: Uses `canvas.clipPath` for the rounded corner effect.
