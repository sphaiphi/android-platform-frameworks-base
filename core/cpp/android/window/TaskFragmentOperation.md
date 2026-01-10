# TaskFragmentOperation - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentOperation` is a Parcelable class encapsulating a single operation to be performed on or with a `TaskFragment`. It is used within `WindowContainerTransaction` to batch hierarchy changes. It supports a wide range of actions from creation/deletion to reordering and custom animations.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Command Pattern Object for TaskFragments.

## Operation Types (IntDef)
*   `OP_TYPE_CREATE_TASK_FRAGMENT` (0)
*   `OP_TYPE_DELETE_TASK_FRAGMENT` (1)
*   `OP_TYPE_START_ACTIVITY_IN_TASK_FRAGMENT` (2)
*   `OP_TYPE_REPARENT_ACTIVITY_TO_TASK_FRAGMENT` (3)
*   `OP_TYPE_SET_ADJACENT_TASK_FRAGMENTS` (4)
*   `OP_TYPE_CLEAR_ADJACENT_TASK_FRAGMENTS` (5)
*   `OP_TYPE_REQUEST_FOCUS_ON_TASK_FRAGMENT` (6)
*   `OP_TYPE_SET_COMPANION_TASK_FRAGMENT` (7)
*   `OP_TYPE_SET_ANIMATION_PARAMS` (8)
*   `OP_TYPE_SET_RELATIVE_BOUNDS` (9)
*   `OP_TYPE_REORDER_TO_FRONT` (10)
*   `OP_TYPE_SET_ISOLATED_NAVIGATION` (11)
*   `OP_TYPE_CREATE_OR_MOVE_TASK_FRAGMENT_DECOR_SURFACE` (12)
*   `OP_TYPE_REMOVE_TASK_FRAGMENT_DECOR_SURFACE` (13)
*   `OP_TYPE_SET_DIM_ON_TASK` (14)
*   `OP_TYPE_SET_DECOR_SURFACE_BOOSTED` (15)
*   `OP_TYPE_SET_PINNED` (16)
*   **Privileged (System only)**: 1001-1004 (Reorder bottom/top, Clear top move, System UI flags).

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mOpType` | `int` | The operation identifier. |
| `mTaskFragmentCreationParams` | `TaskFragmentCreationParams` | Params for create op. |
| `mActivityToken` | `IBinder` | Token for start/reparent ops. |
| `mActivityIntent` | `Intent` | Intent for start activity op. |
| `mBundle` | `Bundle` | Options/metadata. |
| `mSecondaryFragmentToken` | `IBinder` | Token for adjacent/companion ops. |
| `mAnimationParams` | `TaskFragmentAnimationParams` | Custom animation settings. |
| `mBooleanValue` | `boolean` | Generic toggle for various ops. |
| `mSurfaceTransaction` | `SurfaceControl.Transaction` | Transaction to apply with the op. |

## Java-to-C++ Translation Guide

### Polymorphic Command
*   The class acts as a "Fat Command" object containing fields for all possible operations.
*   C++ translation should use a similar structure or a `std::variant` if the parceling can be made efficient.

### Parceling
*   Order: OpType -> CreationParams -> ActivityToken -> ActivityIntent -> Bundle -> SecondaryToken -> AnimationParams -> BooleanValue -> SurfaceTransaction.

## Implementation Risks
*   **SurfaceControl Transaction**: Parceling a `SurfaceControl.Transaction` across IPC is complex and must match the native `SurfaceComposerClient::Transaction` parceling logic.
