# DestroyActivityItem - Reverse Engineering Documentation

## Executive Summary
`DestroyActivityItem` is a lifecycle item that requests the destruction of an activity (`ON_DESTROY`). It handles the cleanup sequence, including optional finishing of the activity.

## Architecture Overview
- **Inheritance**: Extends `ActivityLifecycleItem`.
- **Role**: Lifecycle request for destruction.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `preExecute`
**Purpose**: Marks the activity as "to be destroyed" in the client.
**Algorithm**:
1. Adds `this` to `client.getActivitiesToBeDestroyed()` map.

### `execute`
**Purpose**: Performs the destruction.
**Algorithm**:
1. Trace `activityDestroy`.
2. Call `client.handleDestroyActivity(...)`.
3. End trace.

### `postExecute`
**Purpose**: Cleanup.
**Algorithm**:
1. Removes the token from `client.getActivitiesToBeDestroyed()`.

### `getTargetState`
**Returns**: `ON_DESTROY`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mFinished` | `boolean` | Whether the activity is finishing (permanently destroyed) or just being destroyed for config change. |

### Serialization (Parcelable)
- **Flattening**:
  - Super write.
  - `writeBoolean(mFinished)`.
- **Unflattening**:
  - Super read.
  - `readBoolean()`.

## Java-to-C++ Translation Guide

### State Tracking
- The `ActivitiesToBeDestroyed` map in `ClientTransactionHandler` needs a C++ equivalent to track pending destructions, which is crucial for race condition handling (e.g., ignoring other transactions for a destroying activity).

## Implementation Risks
- **Race Conditions**: The `preExecute` registration is vital to prevent subsequent transactions from trying to act on a dying activity.
