# NotificationListenerService - Reverse Engineering Documentation

## Executive Summary
`NotificationListenerService` is a powerful service that allows applications to see and interact with all notifications posted to the system. It receives callbacks when notifications are added, removed, or updated, and provides methods to dismiss, snooze, or modify the interruption state (Do Not Disturb).

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `INotificationListener.Stub` (via `NotificationListenerWrapper`).
*   **Permission**: Requires `android.permission.BIND_NOTIFICATION_LISTENER_SERVICE` and explicit user approval in Settings.
*   **Threading**: Since Android N, all callbacks (`onNotificationPosted`, etc.) are executed on the main thread.
*   **Security**: Low-RAM devices and work profiles have specific restrictions on notification access.

## Detailed Functionality

### Core Lifecycle
*   **`onListenerConnected()`**: Called when the service is officially enabled and connected. Safe to call `getActiveNotifications()`.
*   **`onListenerDisconnected()`**: Called when access is revoked or the system unbinds the service.

### Notification Events
*   **`onNotificationPosted(StatusBarNotification sbn, RankingMap rankingMap)`**: Called when a new notification is posted or an existing one is updated.
*   **`onNotificationRemoved(StatusBarNotification sbn, RankingMap rankingMap, int reason)`**: Called when a notification is dismissed by the user, the app, or the system.
*   **`onNotificationRankingUpdate(RankingMap rankingMap)`**: Called when the relative order or importance of active notifications changes.

### Operations
*   **`cancelNotification(String key)`**: Dismisses a specific notification.
*   **`cancelAllNotifications()`**: Dismisses all clearable notifications.
*   **`snoozeNotification(String key, long durationMs)`**: Temporarily removes a notification.
*   **`requestInterruptionFilter(int filter)`**: Requests a change to the system DND state.
*   **`setNotificationsShown(String[] keys)`**: Informs the system that the user has seen these notifications.

### Internal Data Handling
*   **`NotificationListenerWrapper`**: Bridges AIDL calls to the service's handler. It "cleans up" notifications for older clients (populating legacy fields like `largeIcon` from new `Icon` objects).
*   **`RankingMap` / `Ranking`**: Encapsulates the system's assessment of a notification's importance, visibility, and smart features (replies/actions).

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.notification.NotificationListenerService"`
*   **Cancellation Reasons**: `REASON_CLICK`, `REASON_CANCEL`, `REASON_SNOOZED`, `REASON_TIMEOUT`, etc.
*   **Interruption Filters**: `INTERRUPTION_FILTER_ALL`, `PRIORITY`, `NONE`, `ALARMS`.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `INotificationListener.Stub`.
*   **C++**: `BnNotificationListener`.

### Data Structures
*   `StatusBarNotification` and `Notification` are complex Parcelables. Reimplementing them in C++ requires matching the `writeToParcel` / `readFromParcel` logic precisely, especially the "trim" logic (`TRIM_LIGHT` vs `TRIM_FULL`).
*   `RankingMap` is a collection of `Ranking` objects, which contain numerous metadata flags.

### Performance
*   Notification events can be high frequency. The binder interface must be efficient.
*   The "trim" mechanism allows the listener to receive lighter versions of `StatusBarNotification` to save memory and IPC bandwidth.

## Implementation Risks
*   **Privacy**: This service has access to highly sensitive user data (messages, personal info).
*   **System Stability**: A slow listener can delay the appearance of notifications or cause the system UI to hang if it's waiting for listener confirmation (though the system generally uses timeouts).
