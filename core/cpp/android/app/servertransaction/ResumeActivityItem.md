# ResumeActivityItem - Reverse Engineering Documentation

## Executive Summary
`ResumeActivityItem` requests an activity to move to the `ON_RESUME` state.

## Architecture Overview
- **Inheritance**: Extends `ActivityLifecycleItem`.
- **Role**: Lifecycle request (Resume).
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `preExecute`
**Purpose**: Process state update.
**Algorithm**:
1. If `mProcState` is known, update client process state.

### `execute`
**Purpose**: Resumes the activity.
**Algorithm**:
1. Trace `activityResume`.
2. Call `client.handleResumeActivity(...)`.
3. End trace.

### `postExecute`
**Purpose**: Reporting.
**Algorithm**:
1. Call `ActivityClient.activityResumed`.

### `getTargetState`
**Returns**: `ON_RESUME`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mProcState` | `int` | Process state (e.g., top, foreground). |
| `mIsForward` | `boolean` | Is this a forward transition? |
| `mShouldSendCompatFakeFocus` | `boolean` | Game engine compatibility flag. |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Constants
- `ActivityManager.PROCESS_STATE_UNKNOWN` needs C++ constant mapping.

## Implementation Risks
- **Compat Focus**: `mShouldSendCompatFakeFocus` is a hack for legacy apps/games. C++ implementation must propagate this correctly to the window manager/input system.
