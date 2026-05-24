# ActivityTaskManager - Reverse Engineering Documentation

## Executive Summary
`ActivityTaskManager` is a system service wrapper dedicated to managing activity tasks, stacks, and recents. It was split from `ActivityManager` to separate window/activity hierarchy logic from process/service logic.

## Architecture Overview
*   **Pattern**: Service Wrapper / Singleton.
*   **Service**: `IActivityTaskManager`.

## Detailed Functionality

### Task Manipulation
*   `removeTask(int taskId)`: Removes a task.
*   `resizeTask(int taskId, Rect bounds)`: Resizes a task (multi-window).
*   `moveTaskToRootTask`: Re-parenting tasks.

### Root Tasks (Stacks)
*   `getAllRootTaskInfos`: Info about task organizers/stacks.

### Recent Tasks
*   `getRecentTasks`: Retrieves recent task list.

### Lock Task Mode
*   `startSystemLockTaskMode`, `stopSystemLockTaskMode`.

## Java-to-C++ Translation Guide
*   Binder proxy to `IActivityTaskManager`.

## Implementation Risks
*   None.
