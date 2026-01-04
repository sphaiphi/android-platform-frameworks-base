# RemoteAccessibilityController - Reverse Engineering Documentation

## Executive Summary
`RemoteAccessibilityController` manages accessibility interactions for embedded view hierarchies. It acts as a bridge between a host process and an embedded process, ensuring that accessibility services can correctly identify and interact with views inside an embedded window (like `SurfaceControlViewHost`).

## Architecture Overview
*   **Role**: Cross-process accessibility mediator.
*   **Connection**: Manages a `RemoteAccessibilityEmbeddedConnection` wrapper that tracks the binder death of the remote connection.
*   **Threading**: Ensures operations are dispatched to the host view's UI thread.

## Detailed Functionality

### 1. Association
*   **`assosciateHierarchy()`**: Establishes the link between the host's leash and the remote hierarchy.
*   **`disassosciateHierarchy()`**: Cleans up the connection.

### 2. Matrix Management
*   **`setWindowMatrix()`**: Transmits the host-to-embedded coordinate transformation matrix to the remote process.

### 3. Lifecycle
*   **Death Recipient**: Implements `IBinder.DeathRecipient` to automatically clean up the local state if the embedded process crashes.

## Java-to-C++ Translation Guide
*   **IPC**: Uses `IAccessibilityEmbeddedConnection` (AIDL).
*   **Smart Pointers**: In C++, use `sp<IBinder>` and `wp<RemoteAccessibilityController>` for the connection wrapper.

## Implementation Risks
*   **Coordinate Drift**: If the window matrix is not updated promptly when the host view moves, accessibility hit-testing in the embedded hierarchy will fail.
