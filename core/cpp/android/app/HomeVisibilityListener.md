# HomeVisibilityListener - Reverse Engineering Documentation

## Executive Summary
`HomeVisibilityListener` is a listener that apps can register to be notified when the Home activity (Launcher) becomes visible or hidden.

## Architecture Overview
*   **Implementation**: Registers an `IProcessObserver` with `ActivityManager` (specifically `ActivityTaskManager`) to track process state changes and polls task visibility.
*   **Mechanism**:
    *   On process events (`onForegroundActivitiesChanged`, `onProcessDied`), checks `isHomeActivityVisible()`.
    *   `isHomeActivityVisible()`: Queries `ActivityTaskManager.getTasks()` and checks if the top task is `ACTIVITY_TYPE_HOME` and visible.

## Java-to-C++ Translation Guide
*   **Observer**: Implement `IProcessObserver` stub in C++.
*   **Polling**: The visibility check logic involves querying running tasks.

## Implementation Risks
*   **Performance**: Frequent polling of tasks might be expensive if not optimized.
