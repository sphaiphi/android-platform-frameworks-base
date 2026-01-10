# SliceProvider - Reverse Engineering Documentation

## Executive Summary
`SliceProvider` is the base class for applications wishing to expose Slices. It extends `ContentProvider` and implements a specific protocol over the `call()` method to handle Slice binding, intent mapping, and pinning notifications.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Type**: `abstract class`, extends `ContentProvider`.
*   **Role**: Server-side component hosting the Slice data.

## Detailed Functionality

### 1. IPC Dispatch (`call`)
Overrides `ContentProvider.call` to handle specific method strings:
*   `METHOD_SLICE` ("bind_slice"):
    *   Validates Uri.
    *   Checks permissions via `SliceManager.enforceSlicePermission`.
    *   If permission denied: Returns a special "Permission Request" Slice.
    *   If granted: Calls `onBindSlice`.
    *   Returns Bundle with `EXTRA_SLICE`.
*   `METHOD_MAP_INTENT` ("map_slice"):
    *   Calls `onMapIntentToUri`.
    *   Then `onBindSlice` with result Uri.
*   `METHOD_PIN` / `METHOD_UNPIN`:
    *   Validates caller is SYSTEM_UID.
    *   Calls `onSlicePinned` / `onSliceUnpinned`.

### 2. Permission Handling
**Algorithm**:
1.  Check if caller has access.
2.  If not, create a `PendingIntent` that triggers `ACTION_REQUEST_SLICE_PERMISSION`.
3.  Construct a rudimentary Slice containing:
    *   Title/Shortcut hints.
    *   Action pointing to the permission request Intent.
    *   Text "Allow [App] to show slices?".

### 3. Strict Mode Enforcement
**Method**: `onBindSliceStrict`
**Logic**: Sets `StrictMode` to `detectAll()` and `penaltyDeath()` during `onBindSlice` execution. This forces developers to avoid I/O on the binding thread (usually the main thread).

## Data Model
*   **MIME Type**: `vnd.android.slice`
*   **Extras Keys**: `slice_uri`, `supported_specs`, `slice_intent`, `slice`, `pkg`.

## API Reference

### Abstract Methods (To Implement)
*   `onBindSlice(Uri, Set<SliceSpec>)`: Return the actual Slice.

### Overridable Methods
*   `onSlicePinned(Uri)`: Lifecycle hook.
*   `onSliceUnpinned(Uri)`: Lifecycle hook.
*   `onMapIntentToUri(Intent)`: Resolution logic.

## Java-to-C++ Translation Guide

### ContentProvider Adaptation
*   C++ does not have a direct `ContentProvider` class inheritance equivalent for *implementing* providers usually (it's often done in Java).
*   If implementing a system provider in C++, you need a class deriving from `BnContentProvider` (Binder native stub) and implementing the `call` method to dispatch these commands.

### Looping / ANR Watchdog
*   The class uses a `Handler` and `postDelayed` to detect ANRs (timeouts) during callbacks.
*   C++ implementation should replicate this timeout mechanism if it invokes user-provided callbacks.

## Implementation Risks
*   **Binder Identity**: Correctly managing `Binder.getCallingUid()` / `restoreCallingIdentity()` is crucial for permission checks.
*   **Recursion/Deadlocks**: `onBindSlice` is called synchronously via Binder.

## Questions for C++ Team
*   Are we implementing the *client* side (consuming slices) or the *server* side (hosting slices) in C++? `SliceProvider` is primarily a server-side construct.
