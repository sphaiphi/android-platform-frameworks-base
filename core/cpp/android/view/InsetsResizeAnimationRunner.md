# InsetsResizeAnimationRunner - Reverse Engineering Documentation

## Executive Summary
`InsetsResizeAnimationRunner` is a specialized animation runner used to handle transitions when an insets source (like the Status Bar) changes size without changing its visibility. It provides a "fake" animation that generates consistent `WindowInsetsAnimation.Callback` events for the view hierarchy.

## Architecture Overview
*   **Role**: Inset resizing animator.
*   **Logic**: Interpolates between a "From" `InsetsState` and a "To" `InsetsState`.
*   **Mechanism**: Uses a `ValueAnimator` to drive the fractional progress.

## Detailed Functionality
*   **`applyChangeInsets()`**: Calculates the interpolated frame for the insets source on each frame of the animation.
*   **`onReady()`**: Starts the internal timer once the animation is initialized.

## Java-to-C++ Translation Guide
*   **Animation**: Requires a native `ValueAnimator` or a frame-based interpolation loop.
*   **Math**: Linearly interpolates the `left`, `top`, `right`, and `bottom` values of the `Rect` frames.

## Implementation Risks
*   **Layout Churn**: Resizing animations can trigger heavy layout passes. The system must ensure that these are optimized.
*   **Sync**: If the true window resize happens faster or slower than this runner, visual artifacts may occur.
