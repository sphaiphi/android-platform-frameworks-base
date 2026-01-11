# TaskFragmentOrganizerToken - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentOrganizerToken` is a Parcelable wrapper around the `ITaskFragmentOrganizer` binder interface. It acts as a unique identifier for a specific organizer instance, allowing it to be safely passed through IPC and identified by the `WindowManagerService`.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Opaque Identity Handle.

## Detailed Functionality
*   **Identity**: Equality and hash code are based on the underlying `IBinder` of the organizer interface.
*   **Serialization**: Writes and reads the strong binder interface.

## Java-to-C++ Translation Guide
*   **C++ Type**: `class TaskFragmentOrganizerToken`.
*   **Member**: `sp<ITaskFragmentOrganizer> mRealToken`.
*   **Parceling**: Standard `readStrongBinder` / `writeStrongBinder`.

## Implementation Risks
*   None. Standard identity token.
