# AccessibilityEvent - Reverse Engineering Documentation

## Executive Summary
Represents a UI event fired by the system or an app to notify Accessibility Services. It extends `AccessibilityRecord` and adds event-specific data like event type, time, and package name. It is `Parcelable`.

## Data Model
*   **Event Types**: Constants like `TYPE_VIEW_CLICKED`, `TYPE_VIEW_FOCUSED`, `TYPE_WINDOW_STATE_CHANGED`, etc.
*   **Properties**: `mEventType`, `mEventTime`, `mPackageName`, `mContentChangeTypes`, `mWindowChangeTypes`.
*   **Records**: Can contain a list of `AccessibilityRecord`s (historically used, though often just one record essentially merged into the event).

## Java-to-C++ Translation Guide
*   **Parceling**: Implements `Parcelable`. Needs strict alignment with the C++ `Parcel` implementation for IPC.
*   **Bitmasks**: Uses bitmasks for event types and change types.
