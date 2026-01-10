# InputEventReceiver - Reverse Engineering Documentation

## Executive Summary
`InputEventReceiver` is the foundational class for consuming input events from an `InputChannel`. It provides a low-level callback mechanism (`onInputEvent`) that is triggered whenever the system has new touch, key, or motion data for a window.

## Architecture Overview
*   **Role**: Input data consumer.
*   **JNI Centric**: Wraps a native C++ `InputEventReceiver`.
*   **Lifecycle**: Managed via `nativeDispose()`. Must be explicitly disposed to close the `InputChannel`.
*   **Threading**: Callbacks are delivered on the `Looper` thread the receiver was created on.

## Detailed Functionality

### 1. Dispatch Pipeline
*   **`dispatchInputEvent()`**: (Called from native code) Marshals the event data into a `KeyEvent` or `MotionEvent` and triggers the Java-side callback.
*   **`onInputEvent()`**: The primary extension point for subclasses (like `ViewRootImpl`).

### 2. Event Completion
*   **`finishInputEvent()`**: MUST be called after an event is processed. It notifies the system that the app is ready for the next event and whether the current one was handled.

### 3. Special Events
*   **`onFocusEvent()`**: Notifies when the associated window gains or loses focus.
*   **`onTouchModeChanged()`**: Indicates transitions between touch and non-touch interaction modes.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::InputEventReceiver`.
*   **Event Handling**: In C++, this involves reading from the socket FD provided by the `InputChannel` and unflattening events.

## Implementation Risks
*   **ANR**: Failing to call `finishInputEvent()` will block the input pipeline for the window, quickly leading to an ANR.
*   **Thread Affinity**: All interactions with the receiver must occur on the same `Looper` thread.
