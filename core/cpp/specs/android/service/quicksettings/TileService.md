# TileService - Reverse Engineering Documentation

## Executive Summary
`TileService` is the base class for implementing custom Quick Settings tiles. It allows applications to provide a toggle or action button in the system's Quick Settings panel, enabling users to perform quick actions without opening the full application.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**:
    *   Implements `IQSTileService.Stub` to receive events from System UI (click, listening state).
    *   Uses `IQSService` (obtained via Binder extra) to push state updates back to System UI.
*   **Lifecycle**:
    *   `onTileAdded()`: Called when the user first adds the tile to the panel.
    *   `onStartListening()`: Called when the tile becomes visible (e.g., user pulls down the notification shade). The service should update the `Tile` state here.
    *   `onStopListening()`: Called when the tile is no longer visible.
    *   `onClick()`: Called when the user taps the tile.
    *   `onTileRemoved()`: Called when the user removes the tile from the panel.
*   **Permission**: Requires `android.permission.BIND_QUICK_SETTINGS_TILE`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Sets up the bi-directional communication.
1.  Retrieves `IQSService` and `mTileToken` from intent extras.
2.  Fetches the initial `Tile` object from the system.
3.  Returns an `IQSTileService` binder to the system.

### Operations
*   **`getQsTile()`**: Returns the `Tile` object associated with this service.
*   **`showDialog(Dialog)`**: Displays a dialog and automatically collapses the Quick Settings panel.
*   **`unlockAndRun(Runnable)`**: Prompts the user to unlock the device before executing the provided logic.
*   **`startActivityAndCollapse(Intent/PendingIntent)`**: Launches an activity and closes the QS panel.
*   **`requestListeningState(Context, ComponentName)`**: Static method to request the system to bind to an "Active Tile" so it can push an update.

### Tile Modes
*   **Default Tile**: Bound by the system whenever it's visible.
*   **Active Tile**: Marked via `META_DATA_ACTIVE_TILE`. The system only binds when clicked. The app is responsible for calling `requestListeningState` when it has a background update.

## API Reference

### Constants
*   `ACTION_QS_TILE`: `"android.service.quicksettings.action.QS_TILE"`
*   `META_DATA_ACTIVE_TILE`: `"android.service.quicksettings.ACTIVE_TILE"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IQSTileService.Stub`.
*   **C++**: `BnQSTileService`.
*   **System Proxy**: Uses `IQSService` to call `updateQsTile`.

### UI Integration
*   The `Tile` object is Parcelable. Changes made to it in the service process are only visible in System UI after `tile.updateTile()` is called, which triggers a binder transaction.

## Implementation Risks
*   **Resource Leaks**: Failing to stop background listeners in `onStopListening`.
*   **Responsiveness**: The `onClick` handler should be fast. If a long operation is needed, start a background service or use `PendingIntent`.
*   **Z-Order**: `showDialog` uses a special window type (`TYPE_QS_DIALOG`) to ensure it appears above the panel.
