# WindowlessWindowManager - Reverse Engineering Documentation

## Executive Summary
`WindowlessWindowManager` is a simplistic implementation of the `IWindowSession` interface. instead of managing surfaces as top-level children of a display, it manages them as children of a specific root `SurfaceControl`. this enables the "SurfaceControlViewHost" feature, where an entire view hierarchy from one process can be safely embedded into another process.

## Architecture Overview
*   **Role**: Embedded window manager.
*   **Context**: Typically used within a single process or between a host and a plugin.
*   **Sync**: Uses a `ResizeCompleteCallback` to coordinate geometry changes between the host and the embedded views.

## Detailed Functionality

### 1. Window Management
*   **`addToDisplay()`**: Creates a "Leash" and a "BLAST" surface for the embedded window, then parents them to the provided root surface.
*   **`relayout()`**: Handles resizing and visibility toggling for embedded windows without involving the global `WindowManagerService`.

### 2. Input Handling
*   **`grantInputChannel()`**: Proxies input registration to the "Real" Window Manager session to ensure the embedded surface can receive touch and key events.

### 3. Coordinate Sync
*   **`setInsetsState()`**: Manually pushes inset changes to all managed embedded windows (since they don't receive them automatically from the system).

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::view::WindowlessWindowManager`.
*   **State Management**: Uses a `HashMap<IBinder, State>` to track metadata for each embedded window.

## Implementation Risks
*   **Input Leakage**: Securely managing input tokens (`InputTransferToken`) between the host and embedded process is critical to prevent focus hijacking.
*   **Lifecycle**: Mismatched `remove()` calls will lead to leaked `SurfaceControl` layers in the compositor.
