# DisplayAreaOrganizer - Reverse Engineering Documentation

## Executive Summary
`DisplayAreaOrganizer` is the client-side component for managing DisplayAreas. It allows a process (like SystemUI or Shell) to register itself to organize specific types of DisplayAreas (identified by feature IDs). It handles callbacks for appearance/disappearance and can create/delete persistent TaskDisplayAreas.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` extends `WindowOrganizer`
*   **Role**: Client-side Manager/Organizer.
*   **Dependencies**:
    *   `IDisplayAreaOrganizer` (Stub implementation provided).
    *   `IDisplayAreaOrganizerController` (System server interface).

## Feature Constants
Defines IDs like `FEATURE_SYSTEM_FIRST`, `FEATURE_DEFAULT_TASK_CONTAINER`, `FEATURE_IME`, etc. These map to specific `RootDisplayArea` or `DisplayArea` types in the WindowManager policy.

## Detailed Functionality

### Registration
*   `registerOrganizer(int displayAreaFeature)`: Calls the controller to register `mInterface` (Binder stub) for the given feature. Returns a list of existing DAs.

### Management
*   `createTaskDisplayArea(...)`: Calls controller to create a TDA.
*   `deleteTaskDisplayArea(...)`: Calls controller to delete a TDA.

### Callbacks (`mInterface`)
*   `onDisplayAreaAppeared`: Posts to executor -> `DisplayAreaOrganizer.onDisplayAreaAppeared`.
*   `onDisplayAreaVanished`: Posts to executor -> `DisplayAreaOrganizer.onDisplayAreaVanished`.
*   `onDisplayAreaInfoChanged`: Posts to executor -> `DisplayAreaOrganizer.onDisplayAreaInfoChanged`.

## Java-to-C++ Translation Guide

### Inheritance
*   Inherits from `WindowOrganizer`. C++ implementation should likely follow this hierarchy if `WindowOrganizer` exists in C++.

### Binder
*   Needs to implement `BnDisplayAreaOrganizer` (Native stub) to receive callbacks.
*   Needs to hold `BpDisplayAreaOrganizerController` (Proxy) to make calls.

### Threading
*   Java uses an `Executor`. C++ logic typically handles Binder callbacks on a binder thread pool or posts them to a specific `Looper`/`Handler`.

## Implementation Risks
*   **Permission**: Requires `MANAGE_ACTIVITY_TASKS`.
