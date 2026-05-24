# Transition - Reverse Engineering Documentation

## Executive Summary
The abstract base class for all transitions. It defines the contract for capturing state, creating animators, and managing the lifecycle (start, end, cancel).

## Data Model
-   **State Storage**: `mStartValues`, `mEndValues` (Maps of `TransitionValues`).
-   **Targets**: `mTargets`, `mTargetIds`, `mTargetNames`, `mTargetTypes` (and corresponding excludes). Filtering logic determines which views participate.
-   **Animators**: `mAnimators` (list of created animators).
-   **Run State**: `mNumInstances`, `mEnded`, `mPaused`.

## Key Algorithms
-   **`captureValues`**: Recursive traversal of the view hierarchy to populate start/end values. Checks target filters.
-   **`playTransition`**:
    1.  Matches start/end values (`matchStartAndEnd`). This matches instances to instances, names to names, IDs to IDs, etc.
    2.  Calls `createAnimators` to let subclasses generate animations.
    3.  Runs the animations.
-   **`matchStartAndEnd`**: Critical logic to pair up the state of a view in the start scene with its state in the end scene.

## API Reference
-   `captureStartValues`, `captureEndValues` (Abstract)
-   `createAnimator` (Abstract)
-   `addTarget`, `removeTarget`, `excludeTarget`
-   `setDuration`, `setInterpolator`, `setStartDelay`

## Java-to-C++ Translation Guide
-   **Complexity**: This class handles the "diffing" of the scene graph. The `matchStartAndEnd` logic is complex and handles cases like list items (itemId matching) and reparenting.
-   **Thread Local**: `sRunningAnimators` tracks global animations to cancel conflicts.
-   **Cloning**: Transitions must be cloneable because `TransitionManager` often clones a template.
