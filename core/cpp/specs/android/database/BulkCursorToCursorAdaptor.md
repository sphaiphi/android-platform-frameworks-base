# BulkCursorToCursorAdaptor - Reverse Engineering Documentation

## Executive Summary
`BulkCursorToCursorAdaptor` is the client-side counterpart to `CursorToBulkCursorAdaptor`. It takes an `IBulkCursor` proxy and presents it as a standard `AbstractWindowedCursor`. It fetches data lazily by requesting windows from the remote `IBulkCursor` as the user navigates.

## Architecture Overview
*   **Inheritance**: `AbstractWindowedCursor`.
*   **Role**: Client-side proxy cursor.

## Detailed Functionality

### Initialization
*   `initialize(BulkCursorDescriptor)`: Sets up the `IBulkCursor`, count, column names, and initial window from the descriptor.

### Data Fetching (`onMove`)
*   **Trigger**: Called when `mPos` changes.
*   **Logic**:
    1.  Check if current `mWindow` contains `newPosition`.
    2.  If yes, done.
    3.  If no, call `mBulkCursor.getWindow(newPosition)`.
    4.  `setWindow(newWindow)`.
*   **Optimization**: If `mWantsAllOnMoveCalls` is true, notifies remote `mBulkCursor.onMove` even if window is valid.

### Observer Bridge
*   **Problem**: Client registers local `ContentObserver`. Server needs `IContentObserver`.
*   **Solution**: `mObserverBridge` (AbstractCursor's `SelfContentObserver`) provides an `IContentObserver` via `getContentObserver()` to send to `mBulkCursor.requery`.

### Error Handling
*   **RemoteException**: Logs error, treats remote as dead (often suppresses crash, returns false/null).
*   **StaleDataException**: Thrown if accessing closed cursor.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mBulkCursor` | `IBulkCursor` | Remote interface. |
| `mColumns` | `String[]` | Cached column names. |
| `mCount` | `int` | Cached row count. |

## Java-to-C++ Translation Guide
*   **Proxy Logic**: This class mostly delegates to `IBulkCursor` methods.
*   **State**: Maintains local cache of count/columns to avoid IPC for simple metadata queries.
