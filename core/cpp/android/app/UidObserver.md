# UidObserver - Reverse Engineering Documentation

## Executive Summary
`UidObserver` is a base implementation of the `IUidObserver` AIDL interface where all methods are implemented as no-ops. It serves as a convenience class for system components that want to monitor specific UID-related state changes (like becoming active, idle, or gone) without having to implement every method in the interface.

## Architecture Overview
- **Inheritance**: Extends `IUidObserver.Stub`.
- **Visibility**: Marked as `@hide`, used for internal system communication between the system server and other core processes.

## Detailed Functionality

### Event Hooks
The class defines several virtual methods that map to UID state transitions:
- `onUidActive(int uid)`: Triggered when an app UID transitions to the active state.
- `onUidIdle(int uid, boolean disabled)`: Triggered when a UID becomes idle.
- `onUidGone(int uid, boolean disabled)`: Triggered when all processes for a UID have terminated.
- `onUidStateChanged(int uid, int procState, ...)`: Triggered when the process priority or importance changes.
- `onUidProcAdjChanged(int uid, int adj)`: Triggered when the OOM adjustment for a UID is updated.

## API Reference
- `public void onUidActive(int uid)`
- `public void onUidGone(int uid, boolean disabled)`
- `public void onUidIdle(int uid, boolean disabled)`

## Java-to-C++ Translation Guide
- **Binder Stub**: Implement a C++ class that inherits from `android::app::BnUidObserver`.
- **Event Dispatch**: Subclasses in C++ will override these virtual methods to perform native logic, such as updating internal tracking maps or notifying other native subsystems.

## Implementation Risks
- **Overhead**: Monitoring all UID changes can be heavy. C++ implementations should only register for this observer if necessary and ensure the callbacks are processed efficiently.
- **Timing**: Callbacks occur asynchronously. C++ logic must be robust to the possibility that a UID state has changed again by the time the observer is notified.
