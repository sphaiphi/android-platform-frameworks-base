# InputQueue - Reverse Engineering Documentation

## Executive Summary
`InputQueue` provides a high-level mechanism for an application to receive incoming input events, primarily used by native (NDK) applications or specialized UI components. It manages a pool of active events and coordinates their completion between the system and the application.

## Architecture Overview
*   **Role**: Native-to-Java input bridge.
*   **Lifecycle**: Managed by `CloseGuard`. Uses `nativeInit` to establish a connection with the system's input dispatcher.
*   **Pooling**: Uses an `mActiveInputEventPool` to reuse `ActiveInputEvent` objects and reduce allocation churn.

## Detailed Functionality

### 1. Dispatching
*   **`sendInputEvent()`**: Forwards a `KeyEvent` or `MotionEvent` to the native queue. It tracks the event using a unique ID in `mActiveEventArray`.

### 2. Completion
*   **`finishInputEvent()`**: Triggered by native code when an event is processed. It calls the `onFinishedInputEvent` callback on the associated token.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::InputQueue`.
*   **Reference Management**: Uses `WeakReference<InputQueue>` to allow the Java object to be GC'ed while native code may still be executing.

## Implementation Risks
*   **Threading**: `InputQueue` is typically bound to a specific thread's `Looper`. Accessing it from other threads requires careful synchronization.
*   **ANR**: Mismatched `send`/`finish` calls will cause events to leak in the `mActiveEventArray`, potentially blocking future input dispatch.
