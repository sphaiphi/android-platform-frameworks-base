# WindowInsetsAnimationController - Reverse Engineering Documentation

## Executive Summary
`WindowInsetsAnimationController` is an interface that allows an application to take direct, frame-by-frame control over the animation of system windows (like the IME). by using this controller, an app can synchronize its own layout changes with the physical movement of system bar surfaces, enabling "perfectly synced" transitions.

## Architecture Overview
*   **Role**: App-driven inset animator.
*   **Acquisition**: Obtained via `WindowInsetsController.controlWindowInsetsAnimation()`.
*   **Leash Management**: Provides a way to modify the native `SurfaceControl` leashes of the insets.

## Detailed Functionality

### 1. Control
*   **`setInsetsAndAlpha()`**: The core method. The app passes the desired inset and transparency for the current frame. the system then transforms the underlying surfaces to match.

### 2. State
*   **`isReady()`** / **`isFinished()`** / **`isCancelled()`**: Tracks the lifecycle of the control request.
*   **`getShownStateInsets()`** / **`getHiddenStateInsets()`**: Provides the target boundaries for the animation.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Maps to the native implementation of the insets control logic in `ViewRootImpl`.
*   **Surface Sync**: Directly influences `android::SurfaceControl::Transaction` geometry.

## Implementation Risks
*   **Revocation**: The system can revoke control at any time (e.g., if the window loses focus). the app must handle the `onCancelled` callback gracefully.
*   **Deadlocks**: Since this involves per-frame synchronization between the app and the system server, poorly implemented control loops can stall the UI.
