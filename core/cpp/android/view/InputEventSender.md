# InputEventSender - Reverse Engineering Documentation

## Executive Summary
`InputEventSender` provides a mechanism for an application to send (inject) input events into an `InputChannel`. This is typically used by system components or specialized apps to simulate touch or key events.

## Architecture Overview
*   **Role**: Input data producer.
*   **JNI Centric**: Wraps a native C++ `InputEventSender`.
*   **Threading**: Can be called from any thread. If called from a non-Looper thread, it internally posts to the `Looper` to avoid deadlocks.

## Detailed Functionality

### 1. Injection
*   **`sendInputEvent(seq, event)`**: Marshals a `KeyEvent` or `MotionEvent` and sends it through the native channel. Returns `true` if successful.

### 2. Feedback
*   **`onInputEventFinished()`**: Callback triggered when the receiver at the other end of the channel has processed and finished the event.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::InputEventSender`.
*   **Marshalling**: Requires converting Java event objects into native `KeyEvent` or `MotionEvent` instances before calling `nativeSend...`.

## Implementation Risks
*   **Buffer Overflow**: If the input channel socket buffer is full, `sendInputEvent` will return `false`. The caller must handle this retry logic.
*   **Deadlock**: Calling `sendInputEvent` from a thread that is also reading from the same channel can cause a deadlock if the buffers are full.
