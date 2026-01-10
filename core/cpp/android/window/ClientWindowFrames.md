# ClientWindowFrames - Reverse Engineering Documentation

## Executive Summary
`ClientWindowFrames` is a Parcelable container that holds various `Rect` objects describing the geometry of a window from the client's perspective (or as computed by the server for the client). It includes the actual frame, display frame, parent frame, and attachment info.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` implements `Parcelable`
*   **Role**: DTO for window layout geometry.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `frame` | `Rect` | Actual window bounds. |
| `displayFrame` | `Rect` | Container frame (usually display size), possibly excluding insets. |
| `parentFrame` | `Rect` | Frame referenced for gravity and MATCH_PARENT. |
| `attachedFrame` | `Rect` | (Nullable) Frame of the parent window if attached. |
| `isParentFrameClippedByDisplayCutout` | `boolean` | Flag for cutout clipping. |
| `compatScale` | `float` | Scale factor for compatibility mode (default 1f). |
| `seq` | `int` | Sequence number for ordering updates. |

## Detailed Functionality

### Methods
*   `setTo(ClientWindowFrames other)`: Deep copy of all fields.
*   `readFromParcel(Parcel in)`: Reads fields. Needed for AIDL `out` parameters.
*   `toString()`: Helper for debugging.

## Java-to-C++ Translation Guide

### Data Types
*   `Rect` -> `android::graphics::Rect`.
*   `boolean` -> `bool`.
*   `float` -> `float`.

### Parceling
*   **Order**:
    1.  `frame`
    2.  `displayFrame`
    3.  `parentFrame`
    4.  `attachedFrame` (TypedObject)
    5.  `isParentFrameClippedByDisplayCutout`
    6.  `compatScale`
    7.  `seq`

## Implementation Risks
*   **Nullability**: `attachedFrame` is nullable.
*   **Performance**: This object is passed frequently during window layout/resizing. Efficient C++ struct usage is important.
