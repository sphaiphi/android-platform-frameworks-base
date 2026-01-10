# InputFilter - Reverse Engineering Documentation

## Executive Summary
`InputFilter` allows for the global monitoring and transformation of the system's input event stream before events are dispatched to applications. It is installed at the `WindowManagerService` level and is primarily used for accessibility features (e.g., screen magnification, touch exploration).

## Architecture Overview
*   **Role**: Global input interceptor.
*   **Communication**: Implements `IInputFilter.Stub` (Binder interface).
*   **Internal Pipeline**:
    1.  `filterInputEvent()`: Receives an event from the system.
    2.  `onInputEvent()`: Subclasses implement this to modify or drop the event.
    3.  `sendInputEvent()`: Sends the (potentially modified) event back to the system for dispatch.

## Detailed Functionality

### 1. Consistency Verification
*   Uses `InputEventConsistencyVerifier` for both inbound and outbound events to ensure that filtering doesn't break the state of input devices.

### 2. Policy Management
*   **Flags**: Filtered events carry policy flags (e.g., `FLAG_PASS_TO_USER`). If a filter clears this flag, the event will be dropped by the dispatcher.

## Java-to-C++ Translation Guide
*   **Service Integration**: Used by `WindowManagerService`. In C++, this would be a component in the `InputDispatcher` logic.
*   **Threading**: Uses an internal `Handler` (`H`) to ensure all filtering logic is processed on a single thread.

## Implementation Risks
*   **Global Latency**: Since all input passes through the filter, slow processing here will increase touch latency for the entire system.
*   **State Mismatch**: If a filter modifies a gesture (e.g., swallowing a Down event but letting a Move through), it can cause crashes in application-level gesture detectors.
