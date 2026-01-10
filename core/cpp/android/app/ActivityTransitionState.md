# ActivityTransitionState - Reverse Engineering Documentation

## Executive Summary
`ActivityTransitionState` manages the state and persistence of Activity Transitions. It acts as a container and manager for `EnterTransitionCoordinator` and `ExitTransitionCoordinator`, handling the saving and restoring of state across configuration changes and process death.

## Architecture Overview
*   **Package**: `android.app`
*   **Role**: State holder and delegate for `Activity` transition logic.
*   **Relationships**:
    *   Owned by `Activity`.
    *   Manages instances of `EnterTransitionCoordinator` and `ExitTransitionCoordinator`.

## Detailed Functionality

### State Persistence
**Purpose**: Preserve transition information (e.g., pending exit shared elements) across activity recreation.
**Mechanism**:
*   `saveState(Bundle)`: Saves `mPendingExitNames`, `mExitingFrom`, `mExitingTo`.
*   `readState(Bundle)`: Restores these lists from the bundle.

### Coordinator Management
**Purpose**: Create and track coordinators.
**Methods**:
*   `addExitTransitionCoordinator`: Stores a weak reference to active exit coordinators to prevent memory leaks while keeping track of them.
*   `startExitOutTransition`: Initiates exit transition for a new activity launch.
*   `startExitBackTransition`: Initiates return transition (Back button).
*   `enterReady`: Signals that the activity is ready to start the enter transition (views laid out).

### Enter Transition Logic
**Purpose**: Handle the incoming transition.
**Flow**:
1.  `setEnterSceneTransitionInfo`: Receives info from `ActivityOptions`.
2.  `enterReady`: Creates `EnterTransitionCoordinator`.
3.  `postponeEnterTransition` / `startPostponedEnterTransition`: Allows waiting for data (e.g., images loading) before animating.

## Data Model
*   `mEnterTransitionCoordinator`: `EnterTransitionCoordinator`.
*   `mReturnExitCoordinator`: `ExitTransitionCoordinator` (for back navigation).
*   `mCalledExitCoordinator`: `ExitTransitionCoordinator` (for launching new activity).
*   `mExitTransitionCoordinators`: `SparseArray<WeakReference<ExitTransitionCoordinator>>`. map of active exit transactions.
*   `mPendingExitNames`: List of shared element names for potential exit.

## API Reference
*   `saveState(Bundle)` / `readState(Bundle)`.
*   `setEnterSceneTransitionInfo(Activity, SceneTransitionInfo)`.
*   `enterReady(Activity)`.
*   `postponeEnterTransition()`.
*   `startPostponedEnterTransition()`.
*   `startExitBackTransition(Activity)`.
*   `startExitOutTransition(Activity, Bundle)`.

## Java-to-C++ Translation Guide

### Weak References
*   Java uses `WeakReference` for coordinators. C++ should use `std::weak_ptr` to avoid cycles and allow cleanup.

### State Bundling
*   Serialization of string lists into `Bundle` (mapped to `Parcel` or `map` in C++).

### Lifecycle Integration
*   Needs hooks into C++ Activity `onSaveInstanceState`, `onCreate`, `onStop`, `onResume`.

## Implementation Risks
*   **Postponement Logic**: Ensuring `startPostponedEnterTransition` is always eventually called is critical to avoid frozen screens.
*   **Memory Leaks**: Management of coordinator references must ensure they are released when transitions finish.
