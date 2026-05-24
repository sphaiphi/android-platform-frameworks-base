# ActivityTransitionCoordinator - Reverse Engineering Documentation

## Executive Summary
`ActivityTransitionCoordinator` is the base class for managing Activity Transitions (both Entrance and Exit). It orchestrates the movement of shared elements and views between the calling Activity and the launched Activity, handling the communication via `ResultReceiver`.

## Architecture Overview
*   **Inheritance**: Extends `ResultReceiver`.
*   **Subclasses**: `EnterTransitionCoordinator`, `ExitTransitionCoordinator`.
*   **Key Dependencies**:
    *   `Window`: To access decor view and transition configurations.
    *   `SharedElementCallback`: For app-customized behavior.
    *   `TransitionManager` & `Transition`: The animation framework.
    *   `GhostView`: For overlaying shared elements.

## Detailed Functionality

### Shared Element Management
**Purpose**: Identify, map, and animate views that persist across activities.
**Algorithm**:
1.  **Mapping**: Matches names provided in `ActivityOptions` to Views in the hierarchy.
2.  **State Capture**: Captures bounds, matrix, and other properties (`captureSharedElementState`).
3.  **Overlaying**: Moves shared elements to the `Overlay` (using `GhostView`) to animate them on top of the scene (`moveSharedElementsToOverlay`).

### Transition Orchestration
**Purpose**: Coordinate the timing of exit and enter animations.
**Mechanism**:
*   Uses `ResultReceiver` to send messages between the two activities.
*   **Messages**:
    *   `MSG_SET_REMOTE_RECEIVER`: Handshake.
    *   `MSG_TAKE_SHARED_ELEMENTS`: Signal to transfer ownership/visibility.
    *   `MSG_EXIT_TRANSITION_COMPLETE`: Signal that exit animation finished.
    *   `MSG_HIDE_SHARED_ELEMENTS`: Signal to hide original views.

### View Visibility
**Purpose**: Hide views that are transitioning or being replaced by shared elements.
**Mechanism**: Maintains list of `mTransitioningViews` and `mSharedElements`. Uses `setTransitionAlpha` and `setVisibility`.

## Data Model
*   `mSharedElements`: List of Views acting as shared elements.
*   `mSharedElementNames`: Corresponding transition names.
*   `mTransitioningViews`: Views participating in the scene transition (non-shared).
*   `mResultReceiver`: Interface to the remote activity's coordinator.
*   `mEpicenterCallback`: Logic to determine transition epicenter (usually the touched view or first shared element).

## API Reference
*   `viewsReady(ArrayMap)`: Called when shared element views are laid out and ready.
*   `startTransition(Runnable)`: Initiates the transition logic.
*   `stop()`: Cancels/clears state.
*   `onReceiveResult(int, Bundle)`: Handler for cross-process messages.

## Java-to-C++ Translation Guide

### UI Framework Dependency
*   Heavily dependent on the Android View system (`View`, `ViewGroup`, `Matrix`, `Rect`).
*   Requires C++ equivalents for `Transition` framework (`TransitionSet`, `TransitionListener`).

### GhostView
*   The `GhostView` concept (rendering a view in an overlay while keeping it in the layout) is complex. C++ UI framework needs a similar mechanism for z-ordering overrides during animations.

### IPC
*   `ResultReceiver` implies Binder IPC. C++ implementation needs a way to send async messages between the Activity objects (or their proxies).

## Implementation Risks
*   **Synchronization**: Coordinating animations across two separate windows/processes is race-prone. The logic for `MSG_TAKE_SHARED_ELEMENTS` vs `MSG_EXIT_TRANSITION_COMPLETE` must be precise.
*   **Visual Artifacts**: Incorrect matrix calculations or ghost view handling results in flickering or jumping elements.
*   **Lifecycle**: Ensuring the coordinator is cleaned up if the activity dies unexpectedly.
