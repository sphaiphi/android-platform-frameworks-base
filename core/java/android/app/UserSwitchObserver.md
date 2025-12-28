# UserSwitchObserver - Reverse Engineering Documentation

## Executive Summary
`UserSwitchObserver` is a base implementation of the `IUserSwitchObserver` AIDL interface. It provides no-op implementations for callbacks related to user switching events, such as before a switch starts, when a switch occurs, and when a switch is complete. It ensures that the mandatory `IRemoteCallback` signal is sent back to the system server for mandatory steps in the user switch sequence.

## Architecture Overview
- **Inheritance**: Extends `IUserSwitchObserver.Stub`.
- **Visibility**: Marked as `@hide`, used for internal system communication between the `ActivityManager` and other trusted processes.

## Detailed Functionality

### Signal Management
**Mechanism**:
- `onBeforeUserSwitching(int newUserId, IRemoteCallback reply)`: Triggered early in the switch process. It automatically calls `reply.sendResult(null)` to allow the system to proceed.
- `onUserSwitching(int newUserId, IRemoteCallback reply)`: Triggered during the actual switch. Also automatically signals completion.

### Lifecycle Hooks
The class provides empty methods for subclasses to override:
- `onUserSwitchComplete(int newUserId)`
- `onForegroundProfileSwitch(int newProfileId)`
- `onLockedBootComplete(int newUserId)`

## API Reference
- `public void onUserSwitching(int newUserId, IRemoteCallback reply)`
- `public void onUserSwitchComplete(int newUserId)`

## Java-to-C++ Translation Guide
- **Binder Stub**: Implement a C++ class that inherits from `android::app::BnUserSwitchObserver`.
- **Callback Pattern**: Replicate the `if (reply != null) reply->sendResult(nullptr)` pattern in C++ to ensure the system switch state machine doesn't hang.

## Implementation Risks
- **Switch Latency**: Any work done in `onUserSwitching` blocks the overall system user switch. C++ implementations should be extremely efficient.
- **Binder Validity**: Always check if the `reply` proxy is non-null and handle potential `RemoteException` during signal delivery.
