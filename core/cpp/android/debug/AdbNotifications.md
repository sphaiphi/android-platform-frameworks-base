# AdbNotifications - Reverse Engineering Documentation

## Executive Summary
`AdbNotifications` is a utility class responsible for creating status bar notifications related to ADB connections (e.g., "Wireless debugging connected").

## Architecture Overview
- **Dependencies**: `android.app.Notification`, `android.app.PendingIntent`.
- **Role**: UI/UX feedback for ADB state.

## Detailed Functionality

### `createNotification`
**Purpose**: Builds a persistent notification indicating ADB is active.
**Input**: `Context`, `transportType` (USB/WIFI).
**Logic**:
1.  Selects string resources based on transport type (USB vs. WiFi).
2.  Creates a `PendingIntent` that opens Developer Settings (`Settings.ACTION_APPLICATION_DEVELOPMENT_SETTINGS`).
3.  Builds a high-priority, ongoing notification on the `DEVELOPER_IMPORTANT` channel.
4.  Sets the TV extension channel ID if running on TV.

**Java-Specific Notes**:
- **Notification Channels**: Uses `SystemNotificationChannels.DEVELOPER_IMPORTANT`.
- **PendingIntent**: Uses `FLAG_IMMUTABLE`.

## Java-to-C++ Translation Guide
- **UI Logic**: This logic is strictly UI-related. In a pure C++ environment without Android's NotificationManager, this might map to a system log or a status LED/icon update mechanism.
