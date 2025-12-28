
# IAccessibilityServiceClient.aidl - Reverse Engineering Documentation

## Executive Summary
`IAccessibilityServiceClient` is a one-way AIDL interface that defines the contract for the Android system server to call *into* an `AccessibilityService`. It represents the "client" in the relationship, which is the service itself. Every method in this interface is a callback that the system invokes to send events and information to the running accessibility service.

## Architecture Overview
*   **One-Way Interface**: The `oneway` keyword at the interface level is a critical optimization. It means that all calls from the system server to the service are non-blocking. The system server makes the call and immediately continues its work without waiting for the service to finish processing the event. This prevents a slow or misbehaving accessibility service from making the entire system unresponsive.
*   **Server-to-Client Communication**: This interface defines the communication channel from the `AccessibilityManagerService` (the server) to the `AccessibilityService` (the client). The client (the service) implements this Binder interface (via `AccessibilityService.Callbacks` and its internal `IAccessibilityServiceClientWrapper`) to receive these calls.
*   **Callback Contract**: The methods defined here constitute the complete set of events an accessibility service can receive from the system, from core accessibility events to more specialized events like gesture detection, magnification changes, and input method integration.

## Detailed Functionality
This interface defines the methods that the system can call on the service.

*   `init(...)`: The first call made to a service after it's bound, providing it with the connection object (`IAccessibilityServiceConnection`) it will use to call back to the system, a unique connection ID, and a window token.
*   `onAccessibilityEvent(...)`: The primary callback for dispatching `AccessibilityEvent`s to the service.
*   `onInterrupt()`: Tells the service to stop its current feedback.
*   `onGesture(...)`: Delivers a detected `AccessibilityGestureEvent`.
*   `onKeyEvent(...)`: Delivers a `KeyEvent` for the service to handle, if it has requested to filter key events.
*   `onMagnificationChanged(...)`: Notifies the service of changes to the screen magnification region and scale.
*   `onSoftKeyboardShowModeChanged(...)`: Notifies the service of changes to the soft keyboard visibility.
*   `onPerformGestureResult(...)`: Provides the result (success/failure) of a programmatically dispatched gesture.
*   `onAccessibilityButtonClicked(...)`: Notifies the service that the dedicated accessibility button in the navigation bar was clicked.
*   `createImeSession(...)`, `startInput(...)`: Methods for managing the `InputMethod` integration, allowing the service to act as an IME.

## Java-to-C++ Translation Guide
*   **Binder Interface**: This AIDL file will be used by the AIDL compiler to generate C++ classes:
    *   `IAccessibilityServiceClient`: The abstract interface.
    *   `BpAccessibilityServiceClient`: The proxy class, used by the system server to make calls.
    *   `BnAccessibilityServiceClient`: The stub/native base class, which the C++ accessibility service's client-side wrapper must inherit from to implement the callbacks.
*   **`oneway` Keyword**: The `oneway` nature of the calls should be preserved. In C++ Binder, this translates to using the `FLAG_ONEWAY` flag when making transactions, which the generated code typically handles automatically. This is crucial for system performance.
*   **`in` Parameters**: The `in` keyword indicates that the data is only being passed from the caller (system) to the callee (service). This is an optimization that the C++ `Parcelable` implementation can use to avoid copying data on the return path.
*   **Custom Types**: All custom `parcelable` types used in this interface (`AccessibilityEvent`, `Region`, `MagnificationConfig`, etc.) must have C++ `Parcelable` implementations that are wire-compatible with their Java counterparts.

## Implementation Risks
*   **Performance**: Since these are `oneway` calls, the service implementation must be prepared to handle a high volume of events without a chance to apply backpressure. The implementation of `onAccessibilityEvent` in particular must be highly efficient.
*   **Callback Implementation**: The C++ service must correctly implement all methods of the `BnAccessibilityServiceClient` stub. A failure to implement a method or a crash within a callback could cause the service to miss critical system events.
*   **State Management**: The service receives its state and events through these callbacks. It must carefully manage its internal state in response to these calls (e.g., updating its representation of the UI when an `onAccessibilityEvent` arrives).

## Questions for C++ Team
*   What is the C++ class that will be responsible for inheriting from `BnAccessibilityServiceClient` and handling these incoming IPC calls?
*   How will the incoming calls, which arrive on Binder threads, be dispatched to the main logic thread of the C++ service to ensure thread safety? (This mirrors the role of the `Handler` in the Java framework).
