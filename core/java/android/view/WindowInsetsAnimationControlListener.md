# WindowInsetsAnimationControlListener - Reverse Engineering Documentation

## Executive Summary
`WindowInsetsAnimationControlListener` is the callback interface used to receive the result of a request to control window insets animations. it notifies the application when the controller is ready, finished, or if the request was cancelled by the system.

## Detailed Functionality
*   **`onReady(controller, types)`**: The primary callback. Provides the `WindowInsetsAnimationController` once the system has established leashes for the requested inset types.
*   **`onFinished(controller)`**: Signals that the animation control cycle has completed.
*   **`onCancelled(controller)`**: Triggered if the system revokes control or the request fails.

## Java-to-C++ Translation Guide
*   **Interface**: Define as a virtual base class in C++.

## Implementation Risks
*   **Delayed Readiness**: `onReady` may be delayed if the keyboard (IME) needs to perform its own internal relayout before granting a leash to the app.
