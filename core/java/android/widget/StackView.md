# StackView - Reverse Engineering Documentation

## Executive Summary
`StackView` is an `AdapterViewAnimator` that displays items in a 3D "stack" of cards. The front item is visible; swiping it reveals the next item. It simulates depth and perspective.

## Architecture Overview
*   **Inheritance**: `AdapterViewAnimator` -> `StackView`.
*   **Role**: 3D Carousel.
*   **Key Components**:
    *   `StackFrame`: Container for each card.
    *   `HolographicHelper`: Generating outlines/glows.
    *   `StackSlider`: Physics/Animation logic.

## Detailed Functionality

### 1. 3D Transforms
*   **Perspective**: Calculates scale and translation (`transformViewAtIndex`) to position items "behind" the front one.
*   **`PERSPECTIVE_SHIFT_FACTOR`**: Controls how much background items stick out.

### 2. Interaction
*   **Swipe**: Tracks touch events (`onTouchEvent`, `VelocityTracker`).
*   **Animation**: `StackSlider` interpolates position (Y-axis), alpha, and rotation (flipping effect) during a swipe.
*   **Gestures**: `GESTURE_SLIDE_UP` / `GESTURE_SLIDE_DOWN`.

### 3. Visuals
*   **Highlight**: Draws a "res outline" (glow) on the front card.
*   **Click Feedback**: Flashes a click outline.

## Java-to-C++ Translation Guide
*   **3D Rendering**: Requires `setRotationX/Y`, `setTranslationZ`, or custom matrix manipulation.
*   **Physics**: Custom logic for the stack spring-back and slide.

## Implementation Risks
*   **Performance**: Generating holographic bitmaps (`HolographicHelper`) on the fly is expensive.
*   **Complexity**: The interaction between touch tracking, object animators, and the layout logic is dense.
