
# FingerprintGestureController - Reverse Engineering Documentation

## Executive Summary
`FingerprintGestureController` provides an API for an `AccessibilityService` to listen for and respond to swipe gestures performed on the device's fingerprint sensor. It allows services to register callbacks to be notified when a gesture is detected or when the availability of gesture detection changes.

## Architecture Overview
*   **Controller Pattern**: This is a `final` class that encapsulates a specific piece of functionality. An `AccessibilityService` obtains an instance of this controller via `AccessibilityService.getFingerprintGestureController()`.
*   **IPC Client**: The controller acts as a client to the system's accessibility service. It holds a Binder proxy (`IAccessibilityServiceConnection`) to communicate requests, such as checking gesture availability, to the system server.
*   **Callback Mechanism**: It uses a callback-based model for dispatching events. Services register an implementation of the `FingerprintGestureCallback` abstract class. The controller maintains a map of these callbacks and their associated `Handler`s to ensure notifications are delivered on the correct thread.
*   **Event Dispatch**: The controller has `on...` methods (`onGestureDetectionActiveChanged`, `onGesture`) that are called *by* the `AccessibilityService`'s internal machinery when it receives events from the system server. The controller then dispatches these events to its registered callbacks.

## Detailed Functionality

### `isGestureDetectionAvailable()`
*   **Purpose**: To query the system and determine if the fingerprint sensor is currently available for gesture detection. It might be unavailable if it's being used for authentication.
*   **Algorithm**:
    1.  Makes an IPC call (`mAccessibilityServiceConnection.isFingerprintGestureDetectionAvailable()`) to the system server.
    2.  Returns the boolean result.
    3.  Catches `RemoteException` and re-throws it as a `RuntimeException`, a common Android pattern.
*   **C++ Implementation Guidance**: This would be a method on the C++ controller class that makes an equivalent IPC call to the system service and returns the result.

### `registerFingerprintGestureCallback(...)`
*   **Purpose**: To add a callback that will be notified of fingerprint gesture events.
*   **Algorithm**:
    1.  Takes a `FingerprintGestureCallback` and an optional `Handler`.
    2.  Synchronizes on `mLock`.
    3.  Stores the callback and handler in the `mCallbackHandlerMap`.
*   **Java-Specific Notes**: The use of a `Handler` allows callbacks to be executed on a specific thread, which is crucial for UI updates or thread-safe service logic.
*   **C++ Implementation Guidance**: The C++ equivalent would store the callback (e.g., as a `std::shared_ptr` to an abstract base class) and a pointer/reference to a C++ event queue or thread object.

### `unregisterFingerprintGestureCallback(...)`
*   **Purpose**: To remove a previously registered callback.
*   **Algorithm**:
    1.  Synchronizes on `mLock`.
    2.  Removes the callback from the `mCallbackHandlerMap`.
*   **C++ Implementation Guidance**: Remove the callback from the map/vector of registered listeners, guarded by a `std::mutex`.

### `onGestureDetectionActiveChanged(boolean active)` and `onGesture(int gesture)`
*   **Purpose**: These are the entry points for the `AccessibilityService` to push system events into the controller for dispatch. They are not intended to be called by developers directly.
*   **Algorithm**:
    1.  Synchronize on `mLock` and create a shallow copy of the `mCallbackHandlerMap`. This prevents crashes if a callback tries to unregister itself during dispatch.
    2.  Iterate through the copied map.
    3.  For each callback:
        a. If a `Handler` is present, `post` a `Runnable` to the handler that will invoke the appropriate callback method (`onGestureDetectionAvailabilityChanged` or `onGestureDetected`).
        b. If the `Handler` is `null`, invoke the callback method directly on the current thread.
*   **C++ Implementation Guidance**: The same pattern of copying the listener list before dispatching is recommended. The C++ code would post a lambda or task to the appropriate event queue.

### `FingerprintGestureCallback` Abstract Class
This nested static class defines the two callback methods that a service must implement:
*   `onGestureDetectionAvailabilityChanged(boolean available)`: Notifies the service when gesture detection is enabled or disabled.
*   `onGestureDetected(int gesture)`: Notifies the service that a specific gesture (e.g., `FINGERPRINT_GESTURE_SWIPE_RIGHT`) has occurred.

## Data Model
*   `mLock`: An `Object` used for synchronization to protect the callback map. In C++, this would be a `std::mutex`.
*   `mAccessibilityServiceConnection`: A Binder proxy (`IAccessibilityServiceConnection`) for making IPC calls to the system server.
*   `mCallbackHandlerMap`: An `ArrayMap` that maps `FingerprintGestureCallback` instances to `Handler` instances. This allows for thread-safe registration and dispatch. In C++, this could be a `std::map<std::shared_ptr<Callback>, std::shared_ptr<EventQueue>>`.

## Java-to-C++ Translation Guide
*   **Callback Class**: The `FingerprintGestureCallback` would become an abstract C++ base class with pure virtual methods.
*   **Constants**: The `FINGERPRINT_GESTURE_*` constants can be defined as a C++ `enum class` or `constexpr` integers.
*   **Handler/Threading**: The `Handler` mechanism for thread-safe callbacks must be replaced with a C++ equivalent, such as posting lambdas to a message queue or event loop.
*   **IPC**: The dependency on `IAccessibilityServiceConnection` means the C++ version needs a corresponding Binder proxy to communicate with the system.
*   **Locking**: `synchronized` should be replaced with `std::mutex` and `std::lock_guard`.

## Implementation Risks
*   **Callback Re-entrancy**: The pattern of copying the callback list before dispatch is critical to prevent crashes when a callback unregisters itself. This must be preserved in the C++ version.
*   **IPC Failures**: `isGestureDetectionAvailable` makes a blocking IPC call. The C++ code must be prepared to handle exceptions or error codes if the system service is unavailable.
*   **Thread Safety**: The callback map is accessed from the service's main thread (for registration) and the `on...` methods (which could be called from a Binder thread). The locking is essential and must be correctly implemented in C++.

## Questions for C++ Team
*   What is the standard C++ pattern in our environment for managing lists of callbacks and dispatching events to them on specific threads?
*   How should the `FingerprintGestureCallback` C++ interface be defined? Should it use `std::shared_ptr` to manage lifetime?
