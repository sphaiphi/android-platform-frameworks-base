# TaskOrganizer - Reverse Engineering Documentation

## Executive Summary
`TaskOrganizer` is the client-side component for managing Tasks. It allows processes (like the Shell) to register for control of tasks in supported windowing modes. It receives callbacks for task lifecycle events (appeared, vanished, info changed) and provides APIs to manipulate root tasks.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` extends `WindowOrganizer`
*   **Role**: Client-side Task Manager.
*   **Key Interfaces**: `ITaskOrganizer`, `ITaskOrganizerController`.

## Detailed Functionality

### Task Lifecycle
*   `onTaskAppeared(...)`: Called when a task enters a managed windowing mode. Provides a `Leash` (`SurfaceControl`).
*   `onTaskVanished(...)`: Called when a task is removed or mode changes.
*   `onTaskInfoChanged(...)`: Called when task properties (e.g., resizability) change.

### Starting Windows (Splash Screens)
*   `addStartingWindow(...)`: Client is responsible for rendering the initial splash screen for a task.
*   `removeStartingWindow(...)`: Cleanup callback.

### Root Task Management
*   `createRootTask(...)`: Requests creation of a persistent root task on a specific display.
*   `deleteRootTask(...)`: Deletion.

## Java-to-C++ Translation Guide

### Binder Implementation
*   Implement `BnTaskOrganizer` to receive callbacks from System Server.
*   Use an `Executor` (native thread or looper) to handle callbacks asynchronously to avoid blocking binder threads.

### Permission Enforcement
*   Requires `MANAGE_ACTIVITY_TASKS` for most operations.

## Implementation Risks
*   **Leash Management**: The client MUST release the `SurfaceControl` leashes provided in `onTaskAppeared` to avoid resource leaks in the graphics system.
