# ActivityClient - Reverse Engineering Documentation

## Executive Summary
`ActivityClient` is a singleton helper class that facilitates communication between an Activity (client-side) and the system server (specifically `ActivityTaskManagerService` via `IActivityClientController`). It abstracts the IPC binder calls required for activity lifecycle management and other system interactions.

## Architecture Overview
*   **Pattern**: Singleton.
*   **Package**: `android.app`.
*   **Key Dependencies**:
    *   `IActivityClientController` (AIDL interface).
    *   `ActivityTaskManager` (to retrieve the service).
    *   `Singleton` (internal utility).

## Detailed Functionality

### Service Connection
**Purpose**: lazily connects to `ActivityTaskManager` to get the `IActivityClientController`.
**Mechanism**: Uses a `Singleton` helper to fetch `ActivityTaskManager.getService().getActivityClientController()`.

### Activity Lifecycle Reporting
**Purpose**: Reports state changes to the system server.
**Methods**:
*   `activityIdle`: Main thread is idle.
*   `activityResumed`: `onResume` completed.
*   `activityPaused`: `onPause` completed.
*   `activityStopped`: `onStop` completed.
*   `activityDestroyed`: `onDestroy` completed.

### Task & Stack Management
**Purpose**: Manipulate task placement and activity finishing.
**Methods**:
*   `moveActivityTaskToBack`: Moves the task to back.
*   `finishActivity`: Finishes an activity.
*   `finishActivityAffinity`: Finishes activities with same affinity.

### Configuration & UI
**Purpose**: Handling configuration overrides, requested orientation, and window modes.
**Methods**:
*   `setRequestedOrientation`: Change screen orientation.
*   `getDisplayId`: Get current display.
*   `setTaskDescription`: Update recent tasks entry.

## Data Model
*   **No internal state** other than the singleton instance and the binder interface cache. It acts purely as a proxy.

## API Reference
(Selected subset of critical methods)
*   `getInstance()`: Returns the singleton.
*   `activityResumed(IBinder token, boolean handleSplashScreenExit)`
*   `activityPaused(IBinder token)`
*   `activityDestroyed(IBinder token)`
*   `finishActivity(IBinder token, int resultCode, Intent resultData, int finishTask)`
*   `setRequestedOrientation(IBinder token, int requestedOrientation)`

## Java-to-C++ Translation Guide

### Singleton Pattern
*   Implement standard C++ Singleton (thread-safe static instance).

### IPC/Binder
*   Requires C++ equivalent of `IActivityClientController` proxy.
*   `IBinder` maps to `android::os::IBinder`.

### Exception Handling
*   Java catches `RemoteException` and rethrows as `RuntimeException`. C++ should handle binder errors (typically via `Status` objects or `expected`).

### Types
*   `Configuration` -> `android::content::res::Configuration`.
*   `Intent` -> `android::content::Intent`.
*   `ComponentName` -> `android::content::ComponentName`.

## Implementation Risks
*   **Binder Stability**: Frequent IPC calls. C++ implementation needs robust error handling for dead objects.
*   **Concurrency**: Singleton access must be thread-safe.
