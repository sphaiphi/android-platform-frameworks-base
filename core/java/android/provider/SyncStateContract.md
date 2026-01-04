# SyncStateContract - Reverse Engineering Documentation

## Executive Summary
`SyncStateContract` defines the schema for tables storing sync state (account + data blob). Used by `ContactsContract`, `CalendarContract`, and `BrowserContract`.

## Architecture Overview
- **Type**: Contract / Helper.
- **Columns**: `account_name`, `account_type`, `data`.

## Detailed Functionality
-   **Helpers**: `get`, `set`, `insert`, `update`, `newSetOperation`. These wrap `ContentProviderClient` or `ContentValues` operations.

## Data Model
-   **Data**: `byte[]` blob holding the sync state (opaque to the provider).

## Java-to-C++ Translation Guide
-   **Blob Handling**: Read/write byte arrays.
