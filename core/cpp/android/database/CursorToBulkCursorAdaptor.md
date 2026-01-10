# CursorToBulkCursorAdaptor - Reverse Engineering Documentation

## Executive Summary
`CursorToBulkCursorAdaptor` wraps a local `Cursor` (specifically a `CrossProcessCursor`) and exposes it as an `IBulkCursor` service. This allows a local cursor to be shared with a remote process. It handles the logic of filling `CursorWindow`s upon request.

## Architecture Overview
*   **Inheritance**: `BulkCursorNative` (Stub).
*   **Implements**: `IBinder.DeathRecipient`.
*   **Role**: The "Server" side of a cross-process cursor.

## Detailed Functionality

### Window Management (`getWindow`)
*   **Algorithm**:
    1.  Moves underlying cursor to `position`.
    2.  Checks if cursor already has a window containing that position.
    3.  If yes, returns that window.
    4.  If no, uses `mFilledWindow` (a shared window owned by this adaptor).
        *   Clears `mFilledWindow`.
        *   Calls `mCursor.fillWindow(position, mFilledWindow)`.
    5.  Acquires reference to window before returning (caller will release).

### Observer Proxying
*   **Problem**: Remote `IContentObserver` needs to be registered with local `Cursor`.
*   **Solution**: `ContentObserverProxy` (inner class).
    *   Extends local `ContentObserver`.
    *   Holds remote `IContentObserver`.
    *   `onChange` (local) -> `mRemote.onChange` (IPC).
    *   Handles `linkToDeath` to cleanup if remote dies.

### Lifecycle
*   **binderDied**: Disposes the cursor.
*   **close**: Closes underlying cursor and `mFilledWindow`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mCursor` | `CrossProcessCursor` | The actual data source. |
| `mFilledWindow` | `CursorWindow` | Reusable window for non-windowed cursors. |
| `mObserver` | `ContentObserverProxy` | Bridge for notifications. |
| `mProviderName` | `String` | For window naming/debugging. |

## Java-to-C++ Translation Guide
*   **Adapter Pattern**: This class adapts `Cursor` interface to `IBulkCursor` interface.
*   **Concurrency**: `synchronized(mLock)` is used heavily. C++ implementation needs `std::mutex`.
*   **Reference Counting**: Must carefully manage `CursorWindow` references when passing them via Binder (acquire before write, release after).
