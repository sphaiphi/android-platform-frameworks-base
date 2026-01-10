# WindowStateResizeItem - Reverse Engineering Documentation

## Executive Summary
`WindowStateResizeItem` delivers a resize event to a window, including new frames, configuration, and insets state.

## Architecture Overview
- **Inheritance**: Extends `WindowStateTransactionItem`.
- **Role**: Window resize.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Resize window.
**Algorithm**:
1. Trace `windowResized` or `windowResizedReport`.
2. `window.resized(...)` with all parameters.
3. Catch `RemoteException` (log warning).
4. End trace.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mFrames` | `ClientWindowFrames` | Window geometry. |
| `mConfiguration` | `MergedConfiguration` | Config. |
| `mInsetsState` | `InsetsState` | Insets. |
| `mActivityWindowInfo` | `ActivityWindowInfo` | Activity window info (optional). |
| `mReportDraw` | `boolean` | Whether to report draw completion. |
| `mForceLayout` | `boolean` | Force layout pass? |
| `mAlwaysConsumeSystemBars` | `boolean` | Flag. |
| `mDisplayId` | `int` | Display ID. |
| `mSyncSeqId` | `int` | Sync sequence ID. |
| `mDragResizing` | `boolean` | Is in drag resizing mode? |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Data Structures
- `ClientWindowFrames` -> C++ equivalent.

## Implementation Risks
- **Parameter Count**: High number of parameters in `window.resized`. Ensure correct ordering and type matching.
