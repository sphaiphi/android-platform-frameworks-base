# BlockedNumberContract - Reverse Engineering Documentation

## Executive Summary
`BlockedNumberContract` defines the contract for the `BlockedNumberProvider`, which stores phone numbers blocked by the user or system. It allows apps (mostly system/carrier apps) to read/write blocked numbers and check if a number is blocked.

## Architecture Overview
- **Type**: Contract Class.
- **Authority**: `com.android.blockednumber`.
- **Inner Classes**:
    -   `BlockedNumbers`: Defines table columns (`_ID`, `COLUMN_ORIGINAL_NUMBER`, `COLUMN_E164_NUMBER`).
    -   `SystemContract`: Defines system-only methods/constants for block suppression (e.g., during emergency calls) and enhanced blocking settings.

## Detailed Functionality
-   **URI**: `content://com.android.blockednumber/blocked`.
-   **Operations**: Insert, Delete, Query. Update is not supported.
-   **Blocking Logic**: Matches against original number or E164 normalized number.
-   **Block Suppression**: Automatically disabled after emergency calls.
-   **Enhanced Blocking**: Keys for blocking private, payphone, unknown numbers, etc.

## Data Model
-   **Columns**: `_id`, `original_number`, `e164_number`.
-   **Methods**: `isBlocked`, `unblock`, `canCurrentUserBlockNumbers`.

## API Reference
-   `isBlocked(Context, String)`: Checks if a number is blocked.
-   `unblock(Context, String)`: Unblocks a number.
-   `SystemContract.shouldSystemBlockNumber(...)`: System-level check including suppression logic.

## Java-to-C++ Translation Guide
-   **ContentProvider Client**: Use a C++ `ContentProviderClient` equivalent to query/insert/delete using the defined URIs and column names.
-   **AIDL**: If interacting via Binder, map `Bundle` extras and method names.
