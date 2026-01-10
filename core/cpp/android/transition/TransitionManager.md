# TransitionManager - Reverse Engineering Documentation

## Executive Summary
Manages the set of transitions that fire when a scene change occurs. It acts as the entry point (`go`, `beginDelayedTransition`).

## Architecture
-   **Static State**: `sPendingTransitions` (list of ViewGroups waiting for layout), `sRunningTransitions`.
-   **Instance State**: Maps `Scene` pairs (From -> To) to specific `Transition` objects.

## Key Algorithms
-   **`beginDelayedTransition(sceneRoot, transition)`**:
    1.  Captures start values of the current scene.
    2.  Registers an `OnPreDrawListener` on the scene root.
    3.  When the next frame is about to draw (meaning layout changes are applied):
        a. Captures end values.
        b. Plays the transition (`transition.playTransition`).
-   **`changeScene`**: Similar to delayed transition but explicitly handles entering/exiting `Scene` objects.

## Java-to-C++ Translation Guide
-   **Layout Lifecycle**: The reliance on `OnPreDrawListener` is specific to the Android View redraw loop. In C++, this hooks into the "Layout Complete" or "Before Paint" signal of the UI framework.
-   **Scene Management**: Maintains state machines for what Scene is currently active.
