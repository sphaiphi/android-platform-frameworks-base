# SelectionEvent - Reverse Engineering Documentation

## Executive Summary
Represents an event in the text selection lifecycle (e.g., selection started, modified, smart selection applied, action clicked). Used for logging and model feedback.

## Data Model
*   **Offsets**: `mAbsoluteStart`, `mAbsoluteEnd`.
*   **Type**: `mEventType` (e.g., `ACTION_COPY`, `EVENT_SELECTION_MODIFIED`).
*   **Session**: `mSessionId`.
*   **Context**: `mPackageName`, `mWidgetType`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
