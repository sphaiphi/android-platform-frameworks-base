# StartActivityItem - Reverse Engineering Documentation

## Executive Summary
`StartActivityItem` requests an activity to move to the `ON_START` state.

## Architecture Overview
- **Inheritance**: Extends `ActivityLifecycleItem`.
- **Role**: Lifecycle request (Start).
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Starts the activity.
**Algorithm**:
1. Trace `startActivityItem`.
2. Call `client.handleStartActivity(r, pendingActions, mSceneTransitionInfo)`.
3. End trace.

### `getTargetState`
**Returns**: `ON_START`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mSceneTransitionInfo` | `SceneTransitionInfo` | Info for scene transitions. |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Data Structures
- `SceneTransitionInfo` -> C++ equivalent.

## Implementation Risks
- None specific.
