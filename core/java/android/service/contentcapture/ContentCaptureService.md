# ContentCaptureService - Reverse Engineering Documentation

## Executive Summary
`ContentCaptureService` is an abstract service that allows the system to capture on-screen content (view hierarchy, text, events) to provide contextual data to other system components (like Autofill, or intelligence services).

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**:
    *   `IContentCaptureService.Stub`: Receives calls from system server (Content Capture flow).
    *   `IContentProtectionService.Stub`: Receives calls for Content Protection (login detection).
    *   `IContentCaptureDirectManager.Stub`: Receives direct calls from apps (to send events).
*   **Manifest**: Requires `android.permission.BIND_CONTENT_CAPTURE_SERVICE`.
*   **Session Management**: Maintains a mapping of `sessionId` to `uid` to verify callers.

## Detailed Functionality

### Core Operations
1.  **Session Lifecycle**: `onCreateContentCaptureSession`, `onDestroyContentCaptureSession`.
2.  **Event Stream**: `onContentCaptureEvent` receives a stream of events (view appeared, text changed, etc.).
3.  **Snapshots**: `onActivitySnapshot` receives bitmap snapshots of activities.
4.  **Data Removal**: `onDataRemovalRequest` handles privacy requests.
5.  **Data Sharing**: `onDataShareRequest` handles binary data sharing.

### `onBind(Intent intent)`
**Purpose**: Binds the service.
**Returns**:
*   `mContentCaptureServerInterface` if action is `SERVICE_INTERFACE`.
*   `mContentProtectionServerInterface` if action is `PROTECTION_SERVICE_INTERFACE`.

### IPC Handlers
*   **`mContentCaptureServerInterface`**: Handles session creation/destruction, snapshots, data removal, data sharing.
*   **`mContentCaptureClientInterface`**: Handles `sendEvents` from the client app. This path is critical for performance; events are batched (`ParceledListSlice`).
*   **`mContentProtectionServerInterface`**: Handles `onLoginDetected` and allowlist updates.

### Security
*   **UID Verification**: `mSessionUids` maps session IDs to app UIDs. `handleSendEvents` verifies that the caller UID matches the session owner.
*   **Caller Mismatch**: Logs security exceptions and stats if UIDs don't match.

## Data Model
*   `ContentCaptureEvent`: Represents a single change or signal (view appeared, text changed, session started).
*   `ContentCaptureContext`: Metadata about the capture session (activity component, flags).
*   `SnapshotData`: Bitmap data.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: Multiple AIDL interfaces implemented as anonymous inner classes.
*   **C++**: `BnContentCaptureService`, `BnContentProtectionService`, `BnContentCaptureDirectManager`.

### Event Processing
*   **Java**: Uses `ParceledListSlice` to batch events. Iterate, verify UID, dispatch to `onContentCaptureEvent`.
*   **C++**: Need efficient event queue processing.

### Data Sharing
*   **Java**: Uses `DataShareReadAdapter` and `Executor` to handle file descriptors asynchronously.
*   **C++**: Likely involves file descriptor passing and a thread pool.

## Implementation Risks
*   **Performance**: High volume of events (text changes, scrolling). Processing must be efficient.
*   **Concurrency**: Multiple sessions from different apps can be active simultaneously.
*   **Memory**: `SnapshotData` can be large.
