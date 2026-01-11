# ActivityThread - Reverse Engineering Documentation

## Executive Summary
`ActivityThread` manages the execution of the main thread in an application process. It is the entry point (`main` method) for the application. It receives IPC calls from the system server (via `ApplicationThread`) and schedules the execution of lifecycle methods for Activities, Services, and Receivers on the main `Looper`.

## Architecture Overview
*   **Role**: Main Application Loop / Handler.
*   **Inner Classes**:
    *   `ApplicationThread`: The Binder interface (`IApplicationThread`) passed to AMS.
    *   `H`: The main `Handler` processing messages (LAUNCH_ACTIVITY, BIND_APPLICATION, etc.).
    *   `ActivityClientRecord`: Bookkeeping for active activities.
    *   `ProviderClientRecord`, `ServiceArgsData`, etc.

## Detailed Functionality

### Initialization (`main`)
*   Prepares the `Looper`.
*   Creates `ActivityThread` instance.
*   Calls `attach` to report to AMS (`attachApplication`).
*   Loops `Looper.loop()`.

### Application Binding (`bindApplication`)
*   Receives configuration, app info, providers from AMS.
*   Creates `LoadedApk` (package info).
*   Creates `ContextImpl` (System Context).
*   Instantiates `Application` object and calls `onCreate`.

### Activity Lifecycle Handling
*   `handleLaunchActivity`: Creates Activity, attaches Context, calls `onCreate`.
*   `handleResumeActivity`, `handlePauseActivity`, `handleStopActivity`, `handleDestroyActivity`: Calls corresponding Activity methods.
*   Manages visibility and state restoration.

### Service & Receiver
*   `handleCreateService`: Instantiates Service, calls `onCreate`.
*   `handleReceiver`: Instantiates BroadcastReceiver, calls `onReceive`.

## Java-to-C++ Translation Guide
*   **Complexity**: Highest. This is the runtime container.
*   **Message Loop**: Needs a `Looper`/`Handler` equivalent.
*   **IPC**: Implements the server-side of `IApplicationThread`.

## Implementation Risks
*   **State Synchronization**: Keeping client state in sync with AMS state is critical.
*   **Concurrency**: Handling Binder callbacks (pool threads) by posting to Main thread.
