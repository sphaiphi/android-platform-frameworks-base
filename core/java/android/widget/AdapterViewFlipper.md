# AdapterViewFlipper - Reverse Engineering Documentation

## Executive Summary
`AdapterViewFlipper` is a subclass of `AdapterViewAnimator` that switches between two or more views derived from an adapter. It essentially animates through the adapter's data set, showing one child at a time. It supports auto-flipping on a timer.

## Architecture Overview
*   **Inheritance**: `AdapterViewAnimator` -> `AdapterViewFlipper`.
*   **Role**: Simple slideshow/carousel widget.

## Detailed Functionality

### 1. Auto-Flipping
*   **`startFlipping()` / `stopFlipping()`**: Controls the timer.
*   **`mFlipRunnable`**: A `Runnable` posted to the handler that calls `showNext()` and re-posts itself after `mFlipInterval`.
*   **Window Visibility**: Pauses flipping when detached or invisible to save resources.

### 2. Properties
*   `flipInterval`: Time between transitions.
*   `autoStart`: Whether to start flipping immediately on attachment.

## Java-to-C++ Translation Guide
*   **Timer**: Use `Handler::postDelayed` or a platform timer.
*   **Logic**: Mostly delegates to `AdapterViewAnimator` for the actual view switching.

## Implementation Risks
*   **Memory Leaks**: Ensure `removeCallbacks` is called on detach to prevent the runnable from keeping the view alive.
