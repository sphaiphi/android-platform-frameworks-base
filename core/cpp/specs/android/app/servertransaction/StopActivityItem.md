# StopActivityItem - Reverse Engineering Documentation

## Executive Summary
`StopActivityItem` requests an activity to move to the `ON_STOP` state.

## Architecture Overview
- **Inheritance**: Extends `ActivityLifecycleItem`.
- **Role**: Lifecycle request (Stop).
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Stops the activity.
**Algorithm**:
1. Trace `activityStop`.
2. Call `client.handleStopActivity(...)`.
3. End trace.

### `postExecute`
**Purpose**: Reporting.
**Algorithm**:
1. Call `client.reportStop(pendingActions)`.
   - **Note**: This uses `pendingActions` which might contain the `StopInfo` runnable populated during `execute` (inside `handleStopActivity`).

### `getTargetState`
**Returns**: `ON_STOP`.

## Data Model

### Serialization (Parcelable)
- No fields.

## Java-to-C++ Translation Guide

### Interaction with PendingActions
- The coupling here is via `PendingTransactionActions`. `handleStopActivity` is expected to populate `StopInfo` into the pending actions, and `postExecute` reads/executes it. This flow must be preserved in C++.

## Implementation Risks
- **Ordering**: `postExecute` depends on `execute` having run and populated the necessary info.
