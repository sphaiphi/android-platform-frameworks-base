# ActivityManager - Reverse Engineering Documentation

## Executive Summary
`ActivityManager` provides information about and interaction with the overall activity state of the system. It interacts with `ActivityManagerService` (AMS). While many responsibilities have moved to `ActivityTaskManager`, AM still handles processes, services, and memory.

## Architecture Overview
*   **Pattern**: Service Wrapper.
*   **Dependencies**: `IActivityManager`.

## Detailed Functionality

### Process Management
*   `getRunningAppProcesses()`: Returns list of running processes.
*   `killBackgroundProcesses(String packageName)`: Requests killing of background processes for a package.
*   `getMyMemoryState()`: Gets memory state of current process.

### Service Management
*   `getRunningServices(int maxNum)`: (Deprecated/Restricted) Returns running services.

### Task Management
*   `getAppTasks()`: Returns tasks associated with the calling application.
*   `moveTaskToFront()`: Reorders tasks.

### Device Configuration
*   `getDeviceConfigurationInfo()`: Returns graphics info (GLES version).
*   `getLauncherLargeIconDensity()`: Icon density info.

### System Actions
*   `clearApplicationUserData()`: Clears app data.

## Java-to-C++ Translation Guide
*   Binder proxy to `IActivityManager`.

## Implementation Risks
*   **Permissions**: Many methods require `REAL_GET_TASKS` or `MANAGE_USERS` which standard apps don't have.
