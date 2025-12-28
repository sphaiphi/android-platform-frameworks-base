# ScreenCaptureCallbackHandler - Reverse Engineering Documentation

## Executive Summary
`ScreenCaptureCallbackHandler` manages the registration and dispatching of callbacks when a screen capture (screenshot or screen record) is attempted on an activity. It interfaces with the `ActivityTaskManager` to register an observer at the system level and ensures that user-provided callbacks are executed on the requested thread. It is designed to notify apps so they can protect sensitive content or log the event.

## Architecture Overview
- **Core Components**:
    - `mActivityToken`: The unique token of the monitored `Activity`.
    - `mObserver`: An internal implementation of `IScreenCaptureObserver.Stub` (Binder stub).
    - `mScreenCaptureRegistrations`: A map linking user callbacks to their execution context (`Executor`).
- **Communication**: Uses `IScreenCaptureObserver` for IPC callbacks from the system server.

## Detailed Functionality

### Registration (`registerScreenCaptureCallback`)
**Purpose**: Starts monitoring for screen captures.
**Algorithm**:
1. Wraps the callback and executor in a `ScreenCaptureRegistration`.
2. Stores the registration in a local map.
3. If this is the first registration for the activity, it calls `ActivityTaskManager.getService().registerScreenCaptureObserver(...)` to establish the system-level link.

### Event Dispatching (`onScreenCaptured`)
**Purpose**: Notifies all registered listeners.
**Mechanism**:
1. The system server calls `onScreenCaptured()` on the `mObserver` Binder stub.
2. The observer iterates through all locally stored registrations.
3. For each registration, it uses the provided `Executor` to run the `onScreenCaptured` hook, ensuring the app's callback runs on the correct thread (e.g., UI thread or a worker thread).

### Unregistration
**Purpose**: Stops monitoring.
**Logic**: Removes the callback from the map. If no more callbacks are registered, it notifies the system server to unregister the observer for that activity token.

## API Reference
- `public void registerScreenCaptureCallback(...)`: Adds a listener.
- `public void unregisterScreenCaptureCallback(...)`: Removes a listener.

## Java-to-C++ Translation Guide
- **Binder Observer**: Implement a C++ class that inherits from `android::app::BnScreenCaptureObserver`.
- **Callback Map**: Use `std::map` with `std::function` or a pointer to a listener interface.
- **Service Integration**: Interface with `IActivityTaskManager` via AIDL in C++.

## Implementation Risks
- **Security Constraints**: If the window has `FLAG_SECURE` set, the system server might not trigger the callback. C++ implementation should respect this system-level behavior.
- **Thread Safety**: Access to `mScreenCaptureRegistrations` must be synchronized to handle concurrent registrations/unregistrations.
- **Deadlocks**: Ensure that dispatching the callback via the `Executor` doesn't block the Binder thread for too long.
