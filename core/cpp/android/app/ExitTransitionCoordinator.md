# ExitTransitionCoordinator - Reverse Engineering Documentation

## Executive Summary
`ExitTransitionCoordinator` manages the exit transition of an Activity. It handles the animation of views *leaving* the screen and the shared elements transitioning *to* the called activity (or back to the caller).

## Architecture Overview
*   **Inheritance**: `ActivityTransitionCoordinator`.
*   **Key Logic**:
    *   Captures shared element state to send to the destination.
    *   Hides shared elements locally while they are being animated by the enter coordinator (or overlay).
    *   Runs the Exit transition for non-shared views.

## Detailed Functionality
*   **Start**: `startExit`. Captures state, notifies remote.
*   **Shared Elements**: `startSharedElementExit`. Uses `SharedElementExitTransition`.
*   **Completion**: `notifyComplete`. Sends `MSG_EXIT_TRANSITION_COMPLETE`.
*   **Restoration**: `resetViews`. Brings views back if the transition is canceled or the activity is re-shown.

## Java-to-C++ Translation Guide
*   Symmetric to `EnterTransitionCoordinator`.

## Implementation Risks
*   **Background Handling**: Often involves fading out the activity background (`Window.setBackgroundDrawable`) to reveal the activity below.
