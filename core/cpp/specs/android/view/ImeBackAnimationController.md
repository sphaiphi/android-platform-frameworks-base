# ImeBackAnimationController - Reverse Engineering Documentation

## Executive Summary
`ImeBackAnimationController` coordinates the predictive back animation for the Soft Keyboard (IME). It allows the IME to animate its appearance (sliding down) in sync with the user's back gesture, providing a seamless transition when the keyboard is being dismissed.

## Architecture Overview
*   **Role**: Predictive back animator for the IME.
*   **Listener**: Implements `OnBackAnimationCallback`.
*   **Controller**: Uses `InsetsController` to drive the actual window inset animations.

## Detailed Functionality

### 1. Gesture Tracking
*   **`onBackStarted()`**: Initializes the animation by requesting control of the IME insets.
*   **`onBackProgressed()`**: Updates the "interpolated progress" based on the user's finger movement.
*   **`onBackInvoked()`**: Triggers the completion of the hide animation.
*   **`onBackCancelled()`**: Reverts the IME to its fully shown state.

### 2. Animation Logic
*   **Peeking**: Uses a `PEEK_FRACTION` (0.1) to limit how much the IME follows the back gesture before it's officially invoked.
*   **Interpolation**: Combines `BackGestureInterpolator` with a final `EMPHASIZED_DECELERATE` curve for the post-commit phase.

## Java-to-C++ Translation Guide
*   **Back Stack**: In C++, this needs to be linked to the system's "Predictive Back" state machine.
*   **Insets**: Directly calls `InsetsController::controlWindowInsetsAnimation`.

## Implementation Risks
*   **Flicker**: If the app uses `SOFT_INPUT_ADJUST_RESIZE` without a proper animation callback, predictive back is disabled to avoid massive layout churn during gestures.
*   **Sync**: The IME hide notification must be sent precisely to the `InputMethodManager` to ensure the internal keyboard state matches the visual state.
