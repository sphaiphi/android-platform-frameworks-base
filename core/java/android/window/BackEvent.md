# BackEvent - Reverse Engineering Documentation

## Executive Summary
`BackEvent` is a value object (DTO) that represents a specific point in time during a back gesture. It contains coordinate data, progress (0-1), and the edge the swipe originated from. It is used to drive predictive back animations.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class`
*   **Role**: Event data holder.
*   **Relationships**: Used by `BackMotionEvent` and `OnBackAnimationCallback`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mTouchX` | `float` | Absolute X location of touch. |
| `mTouchY` | `float` | Absolute Y location of touch. |
| `mProgress` | `float` | 0.0 to 1.0 indicating completion percentage. |
| `mSwipeEdge` | `int` | `EDGE_LEFT` (0), `EDGE_RIGHT` (1), or `EDGE_NONE` (2). |
| `mFrameTimeMillis` | `long` | Timestamp of the frame/event. |

## Detailed Functionality

### Construction
*   Constructors initialize all fields.
*   There is a flag-guarded constructor including `frameTimeMillis` (`FLAG_PREDICTIVE_BACK_TIMESTAMP_API`).

### `getProgress()`
**Purpose**: Returns the linear interpolation of the gesture.
**Notes**: 0 is start, ~1 is end (opposite side of screen). Used to seek animations.

### `getSwipeEdge()`
**Purpose**: Indicates drag origin.
**Values**:
*   `EDGE_LEFT`: 0
*   `EDGE_RIGHT`: 1
*   `EDGE_NONE`: 2 (Button press or hardware key)

## Java-to-C++ Translation Guide

### Data Types
*   `float` -> `float`
*   `long` -> `int64_t`
*   `int` (SwipeEdge) -> `enum class SwipeEdge : int32_t { Left = 0, Right = 1, None = 2 }`

### Immutability
*   The Java class is effectively immutable (all final fields). C++ implementation should prefer `const` members or getters with no setters.

### API Parity
*   Implement getters for all fields.
*   Implement a `toString` equivalent for logging.

## Test Cases & Validation
1.  **Coordinate Precision**: Verify float precision is maintained.
2.  **Progress Range**: Ensure progress is clamped or handled expectedly if inputs are outside [0, 1] (logic logic typically handles clamping, but the DTO just holds the value).
3.  **Edge Constants**: Verify Enum values match Java constants exactly.
