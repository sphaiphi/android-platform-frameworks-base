# BackMotionEvent - Reverse Engineering Documentation

## Executive Summary
`BackMotionEvent` is a Parcelable data wrapper that extends the concept of a `BackEvent` with additional animation metadata, specifically the `RemoteAnimationTarget` of the departing window and a trigger state.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Transport object for back gesture events across IPC.
*   **Relationships**:
    *   Contains data to construct a `BackEvent`.
    *   Holds `RemoteAnimationTarget`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mTouchX` | `float` | Absolute X touch position. |
| `mTouchY` | `float` | Absolute Y touch position. |
| `mFrameTimeMillis` | `long` | Event timestamp. |
| `mProgress` | `float` | 0-1 progress value. |
| `mTriggerBack` | `boolean` | True if the back arrow/gesture is in the "triggered" state. |
| `mSwipeEdge` | `int` | Edge enum. |
| `mDepartingAnimationTarget` | `RemoteAnimationTarget` | Metadata about the window being closed/navigated away from. Nullable. |

## Detailed Functionality

### Serialization (Parcelable)
*   **Write Order**:
    1.  `mTouchX` (float)
    2.  `mTouchY` (float)
    3.  `mProgress` (float)
    4.  `mTriggerBack` (boolean)
    5.  `mSwipeEdge` (int)
    6.  `mDepartingAnimationTarget` (TypedObject)
    7.  `mFrameTimeMillis` (long)

## Java-to-C++ Translation Guide

### Data Types
*   `RemoteAnimationTarget` -> Needs corresponding C++ parcelable implementation.
*   `boolean` -> `bool`

### Memory
*   `RemoteAnimationTarget` is likely a heavy object containing file descriptors (surface controls). Ensure proper ownership transfer or reference counting in C++ (e.g., `sp<RemoteAnimationTarget>`).

### Methods
*   Standard getters for all fields.
*   `toString()` for debugging.

## Implementation Risks
*   **Nullability**: `mDepartingAnimationTarget` can be null. C++ code must handle `nullptr` or `std::optional`.
*   **Parceling Order**: Must match strictly with Java. Note that `mFrameTimeMillis` is written *last* in Java.

## Questions for C++ Team
*   Is `RemoteAnimationTarget` already fully implemented in C++? (It usually resides in `android::view`).
