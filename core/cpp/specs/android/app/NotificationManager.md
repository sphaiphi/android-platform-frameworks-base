# NotificationManager - Reverse Engineering Documentation

## Executive Summary
`NotificationManager` is the primary system service for informing users of background events. It provides APIs to post (`notify`), cancel, and manage notifications, channels, and groups. It also handles advanced features like Do Not Disturb (DND) policies, Zen mode, and bubble configurations.

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.NOTIFICATION_SERVICE`.
- **Backend Communication**: Acts as a client wrapper around the `INotificationManager` AIDL interface.
- **Performance Optimization**: 
    - Uses `IpcDataCache` to cache notification channel and group lookups locally in the process.
    - Implements `RateLimiter` to throttle frequent `notify` and `cancel` calls.
    - Employs an `LruCache` to track the status of recent notifications (enqueued or cancelled).

## Detailed Functionality

### Posting Notifications (`notify`)
**Purpose**: Displays a notification to the user.
**Logic**:
1. Checks for system-level classification/blocking.
2. Applies rate limiting via `mUpdateRateLimiter`.
3. "Fixes" the notification by adding fields from context (ApplicationInfo), canonicalizing sound URIs, and downscaling icons.
4. Enqueues the notification via `INotificationManager.enqueueNotificationWithTag`.

### Channel and Group Management
**Purpose**: Allows apps to create and query their notification categories.
**Mechanism**:
- `createNotificationChannel(s)` / `createNotificationChannelGroup(s)`: Proxies to the system server to persist settings.
- `getNotificationChannel(s)`: Retrieves settings, utilizing the `mNotificationChannelListCache` to avoid redundant IPC.

### Do Not Disturb (Zen Mode)
**Purpose**: Manages global and app-specific notification filtering rules.
**Logic**:
- `setInterruptionFilter`: Changes the current DND state. For newer apps, this may modify an app-specific `AutomaticZenRule` instead of global settings.
- `getConsolidatedNotificationPolicy`: Merges global and active rule policies to determine the effective filtering.

### Bubble Support
**Purpose**: Manages floating window notifications.
**Mechanism**: Queries the system server for bubble preferences (`BUBBLE_PREFERENCE_ALL`, `SELECTED`, `NONE`) and feature enablement.

## API Reference (Key Methods)
- `public void notify(int id, Notification notification)`: Main posting API.
- `public void cancel(int id)`: Removes a notification.
- `public void cancelAll()`: Clears all notifications for the app.
- `public void setNotificationDelegate(String delegate)`: Allows another app to post notifications on your behalf.
- `public boolean isNotificationPolicyAccessGranted()`: Checks for permission to modify DND.

## Java-to-C++ Translation Guide
- **AIDL Mapping**: Use AIDL-generated C++ interface `android::app::INotificationManager`.
- **Cache Implementation**: Replicate the `IpcDataCache` logic using a local map or `android::PropertyInvalidatedCache` wrappers in C++.
- **Rate Limiting**: Use a sliding window algorithm or token bucket for the C++ `RateLimiter`.
- **User ID Handling**: Correctly map `UserHandle` to `int` user IDs for IPC.

## Implementation Risks
- **Concurrency**: Access to `mKnownNotifications` and `mNotificationChannelListCache` must be thread-safe.
- **IPC Overhead**: Excessive calls to `notify` can cause binder pressure. The rate limiting logic is critical for system stability.
- **Policy Complexity**: The logic for merging Zen policies and consolidated policies is intricate and must match the system server's rules exactly.
