# CalendarContract - Reverse Engineering Documentation

## Executive Summary
`CalendarContract` defines the contract for the `CalendarProvider`. It manages calendars, events, attendees, reminders, and instances.

## Architecture Overview
- **Authority**: `com.android.calendar`.
- **Tables**:
    -   `Calendars`: Calendar metadata (name, color, owner).
    -   `Events`: Individual event details.
    -   `Instances`: Occurrences of events (expands recurring events).
    -   `Attendees`: Guests.
    -   `Reminders`: Alerts.
    -   `ExtendedProperties`: Sync adapter extra data.

## Detailed Functionality
-   **URIs**:
    -   `Calendars.CONTENT_URI`.
    -   `Events.CONTENT_URI`.
    -   `Instances.CONTENT_URI` / `CONTENT_BY_DAY_URI` / `CONTENT_SEARCH_URI`.
-   **Syncing**: `CALLER_IS_SYNCADAPTER` query parameter unlocks sync-only columns (`_sync_id`, `dirty`).
-   **Events**: Supports recurrence rules (`RRULE`, `RDATE`, `EXRULE`, `EXDATE`).
-   **Reminders**: `MINUTES`, `METHOD` (Alert, Email, SMS, Alarm).

## Data Model
-   **Columns**: Hundreds of columns defined in inner interfaces (`CalendarColumns`, `EventsColumns`, `AttendeesColumns`).

## API Reference
-   `Instances.query(ContentResolver, projection, begin, end)`.
-   `Attendees.query(...)`.

## Java-to-C++ Translation Guide
-   **Recurrence**: The recurrence rule strings (RRULE) follow RFC 5545 (iCalendar). C++ libraries like `libical` are useful here.
-   **Time**: All times are UTC millis since epoch.
