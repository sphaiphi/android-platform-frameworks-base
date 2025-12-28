# Fragment - Reverse Engineering Documentation

## Executive Summary
`Fragment` represents a modular section of an activity's UI/behavior. It has its own lifecycle, input events, and can be added/removed dynamically.

## Architecture Overview
*   **State Machine**: `INITIALIZING` -> `CREATED` -> `ACTIVITY_CREATED` -> `STOPPED` -> `STARTED` -> `RESUMED`.
*   **Relationships**:
    *   Managed by `FragmentManager`.
    *   Hosted by `FragmentHostCallback`.
    *   Can host child fragments (`mChildFragmentManager`).
    *   Associated with a `View`.

## Detailed Functionality

### Lifecycle Methods
*   `onAttach`, `onCreate`, `onCreateView`, `onActivityCreated`, `onStart`, `onResume`.
*   `onPause`, `onStop`, `onDestroyView`, `onDestroy`, `onDetach`.

### State Management
*   `setArguments`: Construction arguments.
*   `onSaveInstanceState`: Persistence.
*   `setRetainInstance`: Retain instance across config changes.

### UI Integration
*   `onCreateView`: Returns the root view.
*   `getLayoutInflater`: Returns the inflater.
*   `startActivity`/`requestPermissions`: Proxies to host activity.

### Loaders
*   `getLoaderManager`: Access to data loaders (deprecated but core).

## Data Model
*   `mState`: Current integer state.
*   `mIndex`, `mWho`: Identifiers.
*   `mContainerId`, `mFragmentId`, `mTag`: ID/Tag.
*   `mView`: Root view.
*   `mChildFragmentManager`: Manager for nested fragments.

## Java-to-C++ Translation Guide
*   **Core Component**: This is a fundamental building block.
*   **Lifecycle**: The state machine logic is complex and must perfectly match the Activity lifecycle.
*   **View Ownership**: C++ needs shared ownership of the View hierarchy.

## Implementation Risks
*   **State Restoration**: Restoring fragments and their back stack state correctly is the hardest part of the Fragment system.
