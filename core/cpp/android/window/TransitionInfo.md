# TransitionInfo - Reverse Engineering Documentation

## Executive Summary
`TransitionInfo` is the primary data structure for describing a window transition. It contains a collection of `Change` objects (representing containers undergoing visibility or geometry changes) and `Root` objects (defining the animation coordinate spaces). It provides the full context needed by a `TransitionPlayer` to animate multiple windows simultaneously.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Comprehensive transition descriptor.
*   **Inner Classes**: `Change`, `Root`, `AnimationOptions`.

## Data Model (Change)

| Field | Type | Description |
| :--- | :--- | :--- |
| `mContainer` | `WindowContainerToken` | The container changing. |
| `mParent` | `WindowContainerToken` | New parent in the transition hierarchy. |
| `mLastParent` | `WindowContainerToken` | Previous parent (if reparented). |
| `mLeash` | `SurfaceControl` | The leash to animate. |
| `mMode` | `int` | Action (OPEN, CLOSE, TO_FRONT, etc.). |
| `mFlags` | `int` | Change-specific flags (IS_WALLPAPER, TRANSLUCENT, etc.). |
| `mStartAbsBounds` | `Rect` | Geometry before transition. |
| `mEndAbsBounds` | `Rect` | Geometry after transition. |
| `mStartRotation` | `int` | Rotation before. |
| `mEndRotation` | `int` | Rotation after. |
| `mTaskInfo` | `RunningTaskInfo` | (Optional) If it's a task. |
| `mSnapshot` | `SurfaceControl` | (Optional) Visual snapshot for animation. |

## Detailed Functionality

### `isIndependent(Change, TransitionInfo)`
**Purpose**: Logic to determine if a change should be animated on its own or if it's "going along for the ride" with a parent change.
**Algorithm**:
1.  True if no parent.
2.  True if reparented.
3.  False if `TRANSIT_CHANGE` (non-visibility update).
4.  False if inside a parent that is also changing visibility (OPEN/CLOSE).

### `releaseAnimSurfaces()`
Cleans up `mSnapshot` surfaces and root leashes to free memory once animations are finished.

## Java-to-C++ Translation Guide

### Parceling
*   This is a heavy object. Adherence to the write order of the lists (`mChanges`, `mRoots`) and the nested objects is vital.
*   `SurfaceControl` handles are serialized via Binder.

### Coordinate Logic
*   Uses `Point` and `Rect`. Maps to `android::graphics` types.

## Implementation Risks
*   **Lifecycle**: The leashes provided in `TransitionInfo` are owned by the transition. The player must NOT release them until the transition is officially finished.
