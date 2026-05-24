# TaskStackListener - Reverse Engineering Documentation

## Executive Summary
`TaskStackListener` is an abstract base class that implements the `ITaskStackListener` AIDL interface. It provides no-op implementations for all task-related lifecycle callbacks, allowing subclasses to override only the specific events they need to observe. It handles low-level details like hardware buffer cleanup for task snapshots when used across process boundaries.

## Architecture Overview
- **Inheritance**: Extends `ITaskStackListener.Stub`.
- **Core Events**: 
    - Task Changes: `onTaskStackChanged`, `onTaskCreated`, `onTaskRemoved`, `onTaskMovedToFront`.
    - Activity Transitions: `onActivityPinned` (PiP), `onActivityUnpinned`, `onActivityRestartAttempt`.
    - Snapshots: `onTaskSnapshotChanged`.
- **State**: Tracks `mIsRemote` to determine if it's running outside the system server.

## Detailed Functionality

### Snapshot Management (`onTaskSnapshotChanged`)
**Purpose**: Handles updates to the visual thumbnail of a task.
**Logic**: If the listener is remote, it automatically closes the `HardwareBuffer` inside the `TaskSnapshot` to prevent memory leaks in the client process.

### Deprecated Hook Forwarding
**Mechanism**: Several newer callbacks (e.g., `onTaskMovedToFront(RunningTaskInfo)`) automatically forward to their legacy counterparts (e.g., `onTaskMovedToFront(int taskId)`) to maintain backward compatibility for internal listeners.

## API Reference (Key Overrides)
- `public void onTaskStackChanged()`: Triggered when any activity transition or task move occurs.
- `public void onActivityPinned(...)`: Triggered when an activity enters PiP.
- `public void onTaskCreated(...)`: Triggered when a new task is established.
- `public void onTaskSnapshotChanged(...)`: Triggered when a new thumbnail is available.

## Java-to-C++ Translation Guide
- **Binder Stub**: Implement a C++ class inheriting from `android::app::BnTaskStackListener`.
- **Buffer Management**: Use `AHardwareBuffer_release` in the C++ equivalent of `onTaskSnapshotChanged`.
- **Event Dispatch**: If used in a UI-related component, ensure callbacks are dispatched to the appropriate thread via an event loop.

## Implementation Risks
- **IPC Pressure**: Task stack changes occur very frequently. C++ listeners must be lightweight to avoid clogging the system server's dispatch queue.
- **Reference Counting**: `TaskSnapshot` objects contain heavy resources. C++ implementation must match Java's preemptive cleanup logic to avoid GPU memory exhaustion.
