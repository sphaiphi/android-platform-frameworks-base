# InsetsSourceConsumer - Reverse Engineering Documentation

## Executive Summary
`InsetsSourceConsumer` manages the client-side lifecycle of a single `InsetsSource`. it handles the acquisition and release of `InsetsSourceControl` leashes, tracks requested visibility, and coordinates with the `InsetsController` to drive animations.

## Architecture Overview
*   **Role**: Per-source visibility and control mediator.
*   **Logic**: Reacts to control changes from the server (`setControl`) and visibility requests from the app (`requestShow`).

## Detailed Functionality

### 1. Control Management
*   **`setControl()`**: Accepts a new leash from the system server. It determines if an animation is needed to reach the target visibility state.
*   **`applyLocalVisibilityOverride()`**: Enforces the app's requested visibility even if the server state hasn't updated yet.

### 2. Animation
*   **`onAnimationStateChanged()`**: Notifies the consumer that an animation is starting or finishing, allowing it to lock or unlock the insets frame.

### 3. Focus
*   **`onWindowFocusGained()`** / **`UP`**: Tracks window focus to ensure input-related insets (like the IME) are managed correctly.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly associated with a specific `ID` in the native `InsetsState`.
*   **Leash Handling**: C++ implementation must use `android::SurfaceControl` for the animation leash.

## Implementation Risks
*   **Zombie Leashes**: If `setControl(null)` is called but the consumer doesn't release its current leash, native memory and compositor layers will leak.
*   **Stale Insets**: If the `mPendingFrame` logic is incorrect, the view hierarchy may measure against old dimensions while an animation is in progress.
