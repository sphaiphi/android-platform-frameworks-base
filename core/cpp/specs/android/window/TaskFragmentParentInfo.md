# TaskFragmentParentInfo - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentParentInfo` is a Parcelable class providing information about the parent Task of one or more TaskFragments. It includes configuration, visibility, and decoration surface information.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Parent metadata container for embedded fragments.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mConfiguration` | `Configuration` | Full task configuration. |
| `mDisplayId` | `int` | Logical display ID. |
| `mTaskId` | `int` | ID of the parent Task. |
| `mVisible` | `boolean` | Visibility state of the parent Task. |
| `mHasDirectActivity` | `boolean` | True if the Task has direct child activities not in fragments. |
| `mDecorSurface` | `SurfaceControl` | (Nullable) Surface for parent-level decorations. |

## Detailed Functionality

### `equalsForTaskFragmentOrganizer(TaskFragmentParentInfo that)`
**Purpose**: Comparison logic for update dispatching.
**Algorithm**: Checks windowing mode, displayId, taskId, visibility, activity status, and decor surface.

## Java-to-C++ Translation Guide

### Data Types
*   `SurfaceControl` -> `android::view::SurfaceControl`.
*   `Configuration` -> C++ Configuration struct.

### Parceling Order
1.  `mConfiguration`
2.  `mDisplayId`
3.  `mTaskId`
4.  `mVisible`
5.  `mHasDirectActivity`
6.  `mDecorSurface` (TypedObject)

## Implementation Risks
*   **Decor Surface**: Must be handled carefully during IPC to avoid reference leaks.
