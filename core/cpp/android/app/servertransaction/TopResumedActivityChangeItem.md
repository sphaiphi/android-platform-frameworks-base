# TopResumedActivityChangeItem - Reverse Engineering Documentation

## Executive Summary
`TopResumedActivityChangeItem` notifies an activity whether it is the "top resumed" activity in the system (gained or lost top position). This is critical for multi-window/multi-display scenarios where multiple activities might be resumed, but only one is "top" (focused).

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`.
- **Role**: Top state notification.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Delivers state change.
**Algorithm**:
1. Trace `topResumedActivityChangeItem`.
2. Call `client.handleTopResumedActivityChanged(r, mOnTop, ...)`.
3. End trace.

### `postExecute`
**Purpose**: Report loss of top state.
**Algorithm**:
1. If `!mOnTop` (lost top state), call `ActivityClient.activityTopResumedStateLost()`.
   - **Rationale**: Optimization. Loss can be reported immediately. Gain is usually reported after the app acknowledges/handles it.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mOnTop` | `boolean` | True if top resumed, false otherwise. |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Logic
- The `postExecute` reporting logic is asymmetric (only reports loss).

## Implementation Risks
- **Timing**: Accurate reporting of top resumed state is vital for resource contention logic (e.g., camera access).
