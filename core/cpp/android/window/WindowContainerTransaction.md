# WindowContainerTransaction - Reverse Engineering Documentation

## Executive Summary
`WindowContainerTransaction` (WCT) is a primary mechanism for batching multiple hierarchy and configuration changes to `WindowContainer`s in a single IPC call. It is used by organizers (Task, TaskFragment, DisplayArea) to apply transactions atomically. It supports resizing, reordering, reparenting, and starting activities.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Atomic Command Batcher.
*   **Key Inner Classes**: `Change`, `HierarchyOp`.

## Detailed Functionality

### `Change`
Stores state changes for a *single* container.
*   Configuration updates (Bounds, Screen size).
*   Visibility/Focusability flags.
*   PiP callbacks.
*   SurfaceControl transaction to be applied with the change.

### `HierarchyOp`
Stores structural operations that must be executed in order.
*   `HIERARCHY_OP_TYPE_REPARENT`: Move a container to a new parent.
*   `HIERARCHY_OP_TYPE_REORDER`: Move container to top/bottom of siblings.
*   `HIERARCHY_OP_TYPE_LAUNCH_TASK`: Start a task.
*   `HIERARCHY_OP_TYPE_ADD_TASK_FRAGMENT_OPERATION`: Command for TaskFragments.

### Merging
*   `merge(WCT other, boolean transfer)`: Combines another transaction into this one. It merges the `mChanges` map and appends the `mHierarchyOps` list.

## Java-to-C++ Translation Guide

### Data Structures
*   `ArrayMap<IBinder, Change>` -> `std::map<sp<IBinder>, Change>`.
*   `ArrayList<HierarchyOp>` -> `std::vector<HierarchyOp>`.

### Parceling
*   This is an extremely large and complex parcelable.
*   **Order**:
    1.  `mChanges` (Map)
    2.  `mHierarchyOps` (TypedList)
    3.  `mErrorCallbackToken` (StrongBinder)
    4.  `mTaskFragmentOrganizer` (StrongInterface)

### HierarchyOp Parceling
*   Uses an `int` type discriminator, followed by fields specific to that type. C++ implementation should use a `switch` on `mType` during reading.

## Implementation Risks
*   **Transaction Size**: WCTs can become very large. Native binder limits must be considered if transactions involve many containers or nested data.
*   **Ordering**: The `mHierarchyOps` list *must* be processed in the exact order it was built to maintain visual consistency.
