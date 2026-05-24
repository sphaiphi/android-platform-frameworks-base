# StatusBarNotification - Reverse Engineering Documentation

## Executive Summary
`StatusBarNotification` (SBN) is a Parcelable container that wraps a `Notification` object with system-level metadata. It is the primary data structure used by the `NotificationManagerService` to communicate notification state to the System UI and to `NotificationListenerService` implementations.

## Data Model

### Identity Fields
*   **`pkg`**: `String` - The package name of the app that own the notification.
*   **`opPkg`**: `String` - The package name of the app that actually posted the notification (might be different if using a delegate).
*   **`id`**: `int` - The app-provided integer ID.
*   **`tag`**: `String` - The app-provided string tag (nullable).
*   **`uid`**: `int` - The UID of the owning package.
*   **`user`**: `UserHandle` - The user for whom this notification is intended.
*   **`key`**: `String` - A unique system-generated key derived from `user|pkg|id|tag|uid`.

### Content Fields
*   **`notification`**: `Notification` - The actual content (title, text, style, actions, etc.).
*   **`postTime`**: `long` - The system time when the notification was first posted.

### Grouping Fields
*   **`groupKey`**: `String` - Used to group multiple notifications from the same app.
*   **`overrideGroupKey`**: `String` - A system-assigned key that can override the app's grouping.

### Instance Tracking
*   **`mInstanceId`**: `InstanceId` - A stable per-notification ID used for internal logging and analytics.

## API Reference

### Getters
*   `getPackageName()`, `getId()`, `getTag()`, `getUid()`, `getNotification()`, `getUser()`, `getPostTime()`, `getKey()`, `getGroupKey()`.

### Checks
*   `isOngoing()`: Checks if `FLAG_ONGOING_EVENT` is set.
*   `isClearable()`: Returns true if the user can dismiss the notification.
*   `isGroup()`: Returns true if the notification is part of a group.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Writes metadata strings/ints, then delegates to `Notification.writeToParcel`, then writes `UserHandle`, `postTime`, and `overrideGroupKey`.
*   **C++**: `android::Parcelable`.
    *   Must handle `Notification` C++ equivalent if available.
    *   `UserHandle` is a standard system type.

### Context Management
*   The Java implementation has `getPackageContext()`, which creates a `Context` for the notifying app's resources (icons, etc.). In C++, this would likely involve querying `PackageManager` for the app's APK path and using `AssetManager` to load resources.

## Implementation Notes
*   **Key Generation**: The `key()` method is central to identification across the system. C++ logic must match the `user|pkg|id|tag|uid` format.
*   **Cloning**: Supports "shallow" cloning where the inner `Notification` is replaced or "light" cloning where the `Notification` is stripped of heavy fields (bitmaps).
