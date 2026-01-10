# AutofillManager - Reverse Engineering Documentation

## Executive Summary
The main system service manager class (`Context.AUTOFILL_MANAGER_SERVICE`). It allows apps to interact with the Autofill Framework (request autofill, notify view entry/exit, commit/cancel sessions).

## Architecture
*   **Service Wrapper**: `IAutoFillManager` (Binder interface to system_server).
*   **Client Interface**: `IAutoFillManagerClient` (Binder interface for callbacks from system_server).
*   **Session Management**: Tracks `mSessionId`, `mState` (ACTIVE, FINISHED, etc.).
*   **Tracked Views**: `TrackedViews` helper (likely inner class or adjacent) to manage view visibility/state.

## Key Algorithms
*   **`notifyViewEntered`**:
    *   Checks if autofill is enabled.
    *   Starts a new session if needed (via `startSessionLocked`).
    *   Notifies service of view entry (via `updateSessionLocked`).
*   **`requestAutofill`**: Explicitly triggers autofill (manual request).
*   **`autofill`**: Called by service/client to apply values to views.

## Java-to-C++ Translation Guide
*   **Binder**: Heavy IPC usage.
*   **View Integration**: Tight coupling with `View` methods (`getAutofillValue`, `autofill`).
