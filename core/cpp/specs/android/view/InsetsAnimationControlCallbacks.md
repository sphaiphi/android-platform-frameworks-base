# InsetsAnimationControlCallbacks - Reverse Engineering Documentation

## Executive Summary
`InsetsAnimationControlCallbacks` is an internal interface that allows `InsetsAnimationControlImpl` and other animation runners to communicate back to their owner (usually the `InsetsController` or `ViewRootImpl`). it manages the start, scheduling, and finishing of inset animations.

## Architecture Overview
*   **Role**: Animation runner-to-host mediator.
*   **Context**: Used during window inset animations (e.g., keyboard sliding up).

## Detailed Functionality
*   **`startAnimation()`**: Triggers the initial dispatch of `onPrepare` and `onStart` to the view hierarchy.
*   **`scheduleApplyChangeInsets()`**: Requests a frame traversal to apply the latest animation state.
*   **`notifyFinished()`**: Finalizes the animation lifecycle.
*   **`reportPerceptible()`**: Notifies the host whether the animating insets are currently visible to the user.

## Java-to-C++ Translation Guide
*   **Interface**: Define as a pure virtual interface in C++.
*   **Integration**: Implement in the native `InsetsController` equivalent.

## Implementation Risks
*   **Sync Accuracy**: Incorrectly implementation of `scheduleApplyChangeInsets` can lead to stuttering animations if the "apply" pass is not correctly aligned with the display refresh.
