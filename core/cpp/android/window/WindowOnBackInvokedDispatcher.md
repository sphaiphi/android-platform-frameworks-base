# WindowOnBackInvokedDispatcher - Reverse Engineering Documentation

## Executive Summary
`WindowOnBackInvokedDispatcher` is the core implementation of the modern Android back-navigation system for windows. It manages the registration of callbacks, determines the top-priority callback, and coordinates with `WindowManagerService` to enable predictive back animations. It also handles raw touch events to drive animation progress.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` implements `OnBackInvokedDispatcher`
*   **Role**: Window-level Back Navigation Manager.
*   **Key Dependencies**:
    *   `BackTouchTracker`: Calculates swipe progress.
    *   `BackProgressAnimator`: Drives the visual progress smoothing.
    *   `IWindowSession`: IPC to WindowManager.

## Detailed Functionality

### Callback Management
*   **Storage**: Uses a `TreeMap<Integer, ArrayList<OnBackInvokedCallback>>` to store callbacks sorted by priority.
*   **Priority Logic**: Higher priorities are checked first. Within a priority, the most recently added callback is the top.
*   **Dispatch**: Only the "Top" callback is sent to the `WindowManagerService` via `mWindowSession.setOnBackInvokedCallbackInfo`.

### Predictive Back Interaction
1.  **Motion Events**: `onMotionEvent` feeds data to `mTouchTracker`.
2.  **Progress**: `mProgressAnimator` is notified of progress updates from the tracker.
3.  **IPC Wrapper**: `OnBackInvokedCallbackWrapper` (Inner Stub) is the binder object that the system server calls. It handles `onBackStarted`, `onBackProgressed`, etc.

### Compatibility
*   `isOnBackInvokedCallbackEnabled(...)`: Determines if the app has opted into the new back system via the `android:enableOnBackInvokedCallback` manifest attribute.

## Java-to-C++ Translation Guide

### Data Structures
*   `TreeMap<int, vector<OnBackInvokedCallback>>`.
*   `HashMap` for quick lookup.

### Logic
*   **Threading**: Callbacks must be posted to the correct `Handler`/`Looper`. C++ needs equivalent thread dispatching.
*   **Binder**: Implement the stub `BnOnBackInvokedCallback` to handle the IPC events.

## Implementation Risks
*   **State Consistency**: Ensure the "Top" callback in the client matches what the system server thinks is the top.
*   **Resource Management**: Callbacks are binder objects; manage strong/weak pointers carefully to avoid leaks while ensuring callbacks remain valid for dispatch.
