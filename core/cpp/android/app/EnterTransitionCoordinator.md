# EnterTransitionCoordinator - Reverse Engineering Documentation

## Executive Summary
`EnterTransitionCoordinator` manages the entry transition of an Activity. It handles the "entering" views and shared elements coming *from* a previous activity. It reverses the logic of the Exit transition.

## Architecture Overview
*   **Inheritance**: `ActivityTransitionCoordinator`.
*   **Key Logic**:
    *   Receives shared elements from the caller.
    *   Waits for local views to be ready (`viewsReady`).
    *   Animates shared elements from their starting position (received in Bundle) to their final layout position.
    *   Animates entering views (fade in, slide in, etc.).

## Detailed Functionality
*   **Initialization**: `prepareEnter`. Sets initial background (often transparent) and shared element state.
*   **Remote Communication**: Sends `MSG_SET_REMOTE_RECEIVER` to the caller's ExitCoordinator.
*   **Execution**:
    *   `onTakeSharedElements`: Restores shared element state from bundle.
    *   `startEnterTransition`: Runs the `EnterTransition`.
    *   `forceViewsToAppear`: Fallback if transition fails/cancels.

## Java-to-C++ Translation Guide
*   Complex state machine involving UI layout passes and IPC messages.
*   Needs tight integration with the View system (PreDraw listeners).

## Implementation Risks
*   **Flicker**: Coordinating the exact frame where the shared element moves from the caller's window to the callee's window is difficult.
