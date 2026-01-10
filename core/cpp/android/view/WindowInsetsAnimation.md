# WindowInsetsAnimation - Reverse Engineering Documentation

## Executive Summary
`WindowInsetsAnimation` represents an ongoing animation of a set of window insets (e.g., the keyboard sliding up). it provides metadata about the animation's type, progress, duration, and interpolation, allowing applications to choreograph their own UI changes in sync with system bar movements.

## Data Model
*   **`getTypeMask()`**: The set of `InsetsType` currently animating.
*   **`getFraction()`** / **`getInterpolatedFraction()`**: The current progress (0.0 to 1.0).
*   **`mDurationMillis`**: Total length of the animation.
*   **`mAlpha`**: The transparency of the animating windows.

## Detailed Functionality

### 1. The Callback Pipeline (`Callback`)
*   **`onPrepare()`**: Called before the animation starts.
*   **`onStart()`**: Called before the first frame, providing the `Bounds` (start and end insets).
*   **`onProgress()`**: Called on every frame of the animation.
*   **`onEnd()`**: Finalizes the animation.

### 2. Bounds
*   `Bounds` object contains the `lowerBound` (Hidden) and `upperBound` (Shown) `Insets` for the animation cycle.

## Java-to-C++ Translation Guide
*   **Logic**: Primarily involves managing a list of active animations and calculating interpolated fractions.
*   **Integration**: In C++, this should be tied to the `android::uirenderer::Animator` hooks.

## Implementation Risks
*   **Dispatch Mode**: Incorrectly implementing `getDispatchMode()` (STOP vs CONTINUE) can lead to broken inset propagation in complex view hierarchies.
