# IBulkCursor - Reverse Engineering Documentation

## Executive Summary
`IBulkCursor` is an IPC interface (AIDL) that provides a low-level protocol for transferring cursor data between processes. Unlike the standard `Cursor` interface, it is optimized for bulk data transfer using `CursorWindow`s.

## Architecture Overview
*   **Type**: AIDL Interface (`IInterface`).
*   **Role**: The contract between a data provider (server) and a data consumer (client) for cursor operations.

## API Reference
*   `getWindow(int position)`: Returns a `CursorWindow` containing the row at `position`.
*   `onMove(int position)`: Notifies the server of a position change (if `WantsAllOnMoveCalls` is true).
*   `deactivate()`: Deprecated/Legacy.
*   `close()`: Closes the cursor on the server.
*   `requery(IContentObserver)`: Re-executes query. Registers a new observer. Returns row count.
*   `getExtras()`: Returns metadata.
*   `respond(Bundle)`: Out-of-band communication.

## Java-to-C++ Translation Guide
*   **AIDL**: Use the AIDL compiler to generate the C++ `IBulkCursor` interface (header) and Bp/Bn classes.
*   **Method Signatures**: Must match the Java AIDL definition.

## Data Model
*   **Constants**: Transaction codes (`GET_CURSOR_WINDOW_TRANSACTION`, etc.) for manual Binder implementation (though AIDL is preferred).
