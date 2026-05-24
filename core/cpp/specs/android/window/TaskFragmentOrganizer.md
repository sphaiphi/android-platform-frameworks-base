# TaskFragmentOrganizer - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentOrganizer` is the client-side base class for components that manage embedded TaskFragments. It facilitates communication with the `WindowManagerService` to create, remove, and update the hierarchy of activities within a Task. It is primarily used for Activity Embedding (e.g., split-screen views within a single app).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` extends `WindowOrganizer`
*   **Role**: Client Manager / Interface Provider.
*   **Key Interfaces**: `ITaskFragmentOrganizer`, `ITaskFragmentOrganizerController`.

## Detailed Functionality

### Lifecycle and Registration
*   `registerOrganizer(boolean isSystemOrganizer)`: Registers the organizer with the system. System organizers have higher privileges (e.g., receiving `SurfaceControl` handles).
*   `unregisterOrganizer()`: Cleans up.

### Transaction Handling
*   `onTransactionReady(TaskFragmentTransaction)`: Callback invoked by the system when a batch of changes is ready for the organizer to process.
*   `onTransactionHandled(...)`: Client calls this to notify the system that it has processed a transaction and optionally provides a `WindowContainerTransaction` for follow-up changes.

### Static Utilities
*   `isActivityEmbedded(Activity)`: Checks if an activity is currently within an organized TaskFragment and doesn't fill the task bounds.

## Constants (Transition Types)
*   `TASK_FRAGMENT_TRANSIT_NONE` (0)
*   `TASK_FRAGMENT_TRANSIT_OPEN` (1)
*   `TASK_FRAGMENT_TRANSIT_CLOSE` (2)
*   `TASK_FRAGMENT_TRANSIT_CHANGE` (6)
*   `TASK_FRAGMENT_TRANSIT_DRAG_RESIZE` (1017)

## Java-to-C++ Translation Guide

### Binder Stub
*   Implement `BnTaskFragmentOrganizer` to handle incoming `onTransactionReady` calls.
*   Delegate the calls to an `Executor` equivalent (e.g., a worker thread or looper).

### Permission Enforcement
*   C++ implementation of the controller (server-side) must enforce `MANAGE_ACTIVITY_TASKS` if `isSystemOrganizer` is requested.

## Implementation Risks
*   **Recursive Transactions**: Avoid infinite loops where `onTransactionReady` triggers a `WindowContainerTransaction` that immediately causes another `onTransactionReady`.
