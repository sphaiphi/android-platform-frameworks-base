# WindowContextController - Reverse Engineering Documentation

## Executive Summary
`WindowContextController` handles the logic for attaching and detaching a `WindowContext` to/from the WindowManager hierarchy. it acts as the bridge between the local `WindowTokenClient` and the `WindowTokenClientController` (which talks to the system server).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class`
*   **Role**: Attachment Manager.

## Detailed Functionality

### Attachment
*   `attachToDisplayArea(...)`: Calls `WindowTokenClientController` to associate the token with a `DisplayArea`.
*   `attachToWindowToken(IBinder)`: Switches the attachment to a specific window token.

### Lifecycle
*   `detachIfNeeded()`: Cleans up the attachment.
*   `reparentToDisplayArea(...)`: Moves to a new display.

## Java-to-C++ Translation Guide
*   **State Machine**: Tracks `AttachStatus` (Initialized, Attached, Detached, Failed).
*   **Delegation**: Calls into `WindowTokenClientController`.

## Implementation Risks
*   **IllegalStateException**: Throws if `attachToDisplayArea` is called twice.
