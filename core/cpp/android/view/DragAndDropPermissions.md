# DragAndDropPermissions - Reverse Engineering Documentation

## Executive Summary
`DragAndDropPermissions` controls access to content URIs passed during a `DragEvent`. In Android, when a drag-and-drop operation involves URIs, the target application must explicitly "take" these permissions to access the data.

## Architecture Overview
*   **Role**: Content URI permission manager for drag-and-drop.
*   **Lifecycle**: Permissions are bound to the `Activity` that requests them. They are automatically revoked when the activity is destroyed or when `release()` is called.
*   **IPC**: Proxies calls to `IDragAndDropPermissions` in the system server.

## Detailed Functionality

### 1. Acquisition
*   **`take(IBinder activityToken)`**: Binds the permission lifetime to a specific activity.
*   **`takeTransient()`**: Takes the permission for the lifetime of the `DragAndDropPermissions` object itself.

### 2. Cleanup
*   **`release()`**: Manually revokes the permissions when they are no longer needed (e.g., after the drop is processed).

## Java-to-C++ Translation Guide
*   **IPC**: Use the `IDragAndDropPermissions` AIDL interface.
*   **Mapping**: In C++, this can be a simple wrapper around the `sp<IDragAndDropPermissions>` proxy.

## Implementation Risks
*   **Prompt Release**: Apps should call `release()` as early as possible to minimize the duration that sensitive URIs are exposed.
*   **Persistence**: These permissions cannot be persisted; they are only valid for the current drag session and the associated activity instance.
