# PauseActivityItem - Reverse Engineering Documentation

## Executive Summary
`PauseActivityItem` requests an activity to move to the `ON_PAUSE` state. It allows configuring whether the activity is finishing, whether the user is leaving (for auto-PiP logic), and reporting behavior.

## Architecture Overview
- **Inheritance**: Extends `ActivityLifecycleItem`.
- **Role**: Lifecycle request (Pause).
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Pauses the activity.
**Algorithm**:
1. Trace `activityPause`.
2. Call `client.handlePauseActivity(...)` with flags.
3. End trace.

### `postExecute`
**Purpose**: Reporting.
**Algorithm**:
1. If `mDontReport` is false, call `ActivityClient.getInstance().activityPaused(...)`.

### `getTargetState`
**Returns**: `ON_PAUSE`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mFinished` | `boolean` | Is activity finishing? |
| `mUserLeaving` | `boolean` | Did user trigger leave (Home key)? |
| `mDontReport` | `boolean` | Skip reporting to server? |
| `mAutoEnteringPip` | `boolean` | Is this part of auto-PiP transition? |

### Serialization (Parcelable)
- Standard read/write of booleans.

## Java-to-C++ Translation Guide

### Flags
- Boolean flags map directly.

### Dependencies
- `ActivityClient` singleton used in `postExecute` for IPC.

## Implementation Risks
- **State consistency**: `mDontReport` is an optimization (e.g., if server already knows). Misuse could lead to server-client state desync.
