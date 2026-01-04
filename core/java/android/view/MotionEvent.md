# MotionEvent - Reverse Engineering Documentation

## Executive Summary
`MotionEvent` is a complex Parcelable object used to report movement events from touch screens, mice, pens, trackballs, and joysticks. It supports multi-touch (multiple "pointers") and provides detailed axis information (X, Y, pressure, orientation). To optimize performance, `MotionEvent` often batches multiple movement samples from a high-frequency sensor into a single object.

## Architecture Overview
*   **Role**: Primary carrier for all touch and analog movement data.
*   **Pointer Model**: Each finger or tool is a "pointer" with a unique ID that remains constant during a gesture, even if its index in the array changes.
*   **JNI Centric**: Most data access is proxied to a native C++ `MotionEvent` object via `nativeGetX`, etc.

## Detailed Functionality

### 1. Pointer Management
*   **`getPointerCount()`**: Number of active pointers in this event.
*   **`getPointerId(int index)`**: Persistent ID for a pointer.
*   **`findPointerIndex(int id)`**: Maps a persistent ID back to the current array index.

### 2. Actions (Masked)
*   **`getActionMasked()`**: The actual action (e.g., `ACTION_DOWN`, `ACTION_POINTER_UP`).
*   **`getActionIndex()`**: For pointer-specific actions (like `ACTION_POINTER_DOWN`), this returns the index of the pointer that changed.

### 3. Axis Data
*   **`getX()`, `getY()`**: Coordinates in pixels.
*   **`getPressure()`**: Approximate pressure (0.0 to 1.0+).
*   **`getAxisValue(int axis)`**: Retrieves values for joysticks or specialized sensors (e.g., `AXIS_VSCROLL`, `AXIS_TILT`).

### 4. Batching (History)
*   **`getHistorySize()`**: Number of samples in the batch.
*   **`getHistoricalX(int pointerIndex, int pos)`**: Retrieves an older coordinate from the current event's buffer.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::MotionEvent`.
*   **Parceling**: Serialization MUST be bit-for-bit compatible with `frameworks/native/libs/input/Input.cpp`.
*   **Memory Management**: `MotionEvent` is a very high-frequency object. Use a pool of native objects (`android::MotionEvent::obtain()`) to minimize allocation overhead.

## Implementation Risks
*   **Coordinate Space**: Coordinates can be in "window space" (raw) or "view space" (transformed by parent matrices). Incorrect conversion leads to "ghost" touches or offset hits.
*   **Consistency**: A touch stream MUST follow the DOWN -> [POINTER_DOWN] -> [MOVE] -> [POINTER_UP] -> UP sequence. Violating this sequence will crash the `InputEventConsistencyVerifier`.
*   **Performance**: Accessing historical data involves looping through native memory. In C++, use raw pointer iteration over samples if possible for maximum throughput.
