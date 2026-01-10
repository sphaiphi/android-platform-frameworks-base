# SmartspaceService - Reverse Engineering Documentation

## Executive Summary
`SmartspaceService` is an abstract base class for services that provide contextual information (Smartspace targets) to the system UI, such as the "At a Glance" widget on the launcher or lock screen. It manages sessions, handles interaction events, and provides updates for time-sensitive or contextually relevant information.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ISmartspaceService.Stub`.
*   **Session Management**: Uses `SmartspaceSessionId` to manage independent content streams (e.g., one for the launcher, one for the lock screen). It tracks session-specific callbacks in `mSessionCallbacks`.
*   **Threading**: Dispatches binder calls to the main thread via a `Handler`.
*   **Permission**: Requires `android.permission.MANAGE_SMARTSPACE`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `ISmartspaceService` binder interface.

### Session Lifecycle
*   **`onCreateSmartspaceSession(SmartspaceConfig, SmartspaceSessionId)`**: Called when a client starts a new session. `SmartspaceConfig` specifies the UI surface (launcher vs lockscreen).
*   **`onDestroySmartspaceSession(SmartspaceSessionId)`**: Called when the session is closed. The service must clean up any session-specific resources.

### Target Management
*   **`onRequestSmartspaceUpdate(SmartspaceSessionId)`**: Called when the system explicitly pulls for fresh data.
*   **`updateSmartspaceTargets(SmartspaceSessionId, List<SmartspaceTarget>)`**: The service calls this method to push new content to the system UI.
*   **`registerSmartspaceUpdates` / `unregisterSmartspaceUpdates`**: Manage the subscription model for session updates.

### Event Tracking
*   **`notifySmartspaceEvent(SmartspaceSessionId, SmartspaceTargetEvent)`**: Notifies the service about user interactions (clicks, dismissals) or UI events related to the provided targets.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.smartspace.SmartspaceService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ISmartspaceService.Stub`.
*   **C++**: `BnSmartspaceService`.

### Data Model
*   `SmartspaceConfig`, `SmartspaceSessionId`, `SmartspaceTarget`, `SmartspaceTargetEvent` are all Parcelables.
*   `SmartspaceTarget` is complex, containing multiple templates for different UI styles.

### Threading
*   **Java**: Uses `Handler` and `PooledLambda` for dispatch.
*   **C++**: Implementations should ensure thread-safe session tracking, especially when multiple sessions are active concurrently.

## Implementation Risks
*   **Latency**: Smartspace content must be updated promptly to remain relevant (e.g., showing a calendar event exactly when it starts).
*   **Resource Management**: Active sessions must be monitored. If a client dies without calling `destroy`, the service should handle the binder death notification.
*   **Privacy**: Smartspace targets contain personal information (emails, locations). The service must process this data securely and minimize leakage.
