# AbstractCursor - Reverse Engineering Documentation

## Executive Summary
`AbstractCursor` is a base implementation of the `CrossProcessCursor` interface (which extends `Cursor`). It provides common functionality for managing cursor position, lifecycle, and observer registration, reducing the boilerplate required for concrete `Cursor` implementations. It is a fundamental building block for the Android database layer.

## Architecture Overview
*   **Inheritance**: `Object` -> `AbstractCursor` -> `CrossProcessCursor` -> `Cursor`, `Closeable`.
*   **Implements**: `CrossProcessCursor`
*   **Subclasses**: `AbstractWindowedCursor`, `MatrixCursor`, `MergeCursor`.
*   **Key Components**:
    *   `DataSetObservable`: Manages `DataSetObserver`s.
    *   `ContentObservable`: Manages `ContentObserver`s.
    *   `ContentResolver`: Used to register observers on URIs.
    *   `CloseGuard`: Detects resource leaks (cursor not closed).

## Detailed Functionality

### Position Management
*   **Purpose**: Tracks the current row index.
*   **Algorithm**:
    *   `mPos`: Current 0-based index. Initialized to -1.
    *   `moveToPosition(int)`: Validates bounds (-1 to count). Calls `onMove()`.
    *   `move(int)`, `moveToFirst()`, `moveToLast()`, `moveToNext()`, `moveToPrevious()`: Convenience wrappers around `moveToPosition`.
    *   `isFirst()`, `isLast()`, `isBeforeFirst()`, `isAfterLast()`: State checks.
*   **Java-Specific Notes**: `onMove()` is a callback for subclasses to handle window updates or state changes when position changes.

### Observer Management
*   **Purpose**: Notifies listeners of data changes.
*   **State**:
    *   `mDataSetObservable`: For `DataSetObserver` (cursor validity/data change).
    *   `mContentObservable`: For `ContentObserver` (underlying data change).
    *   `mSelfObserver`: A `ContentObserver` that monitors the notification URI to trigger `onChange`.
*   **Mechanism**:
    *   `setNotificationUri()`: Registers a self-observer on a URI via `ContentResolver`.
    *   `onChange()`: Dispatches changes to registered `ContentObserver`s and handles self-invalidation logic.

### Lifecycle
*   **Purpose**: Manages resources.
*   **Methods**:
    *   `close()`: Sets `mClosed` flag, unregisters observers, calls `onDeactivateOrClose`, closes `CloseGuard`.
    *   `deactivate()` (Deprecated): Clears observations but keeps object alive (mostly legacy).
    *   `finalize()`: Last-ditch cleanup.

### Data Access (Abstract/Default)
*   **Abstract**: `getCount()`, `getColumnNames()`, `getString()`, `getShort()`, `getInt()`, `getLong()`, `getFloat()`, `getDouble()`, `isNull()`.
*   **Default**:
    *   `getType()`: Defaults to `FIELD_TYPE_STRING` (assumes text unless overridden).
    *   `getBlob()`: Throws `UnsupportedOperationException`.
    *   `getColumnIndex()`: Iterates `getColumnNames()` (O(N) search). handles case-insensitivity and table prefix stripping (e.g. "table.col" -> "col").

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mPos` | `int` | Current row position (-1 start). |
| `mClosed` | `boolean` | Flag for closed state. |
| `mContentResolver` | `ContentResolver` | Handle to system content resolver. |
| `mNotifyUri` | `Uri` | Primary URI to watch for changes. |
| `mNotifyUris` | `List<Uri>` | List of URIs to watch. |
| `mSelfObserver` | `ContentObserver` | Internal observer for auto-requery/notification. |
| `mDataSetObservable` | `DataSetObservable` | Registry for DataSetObservers. |
| `mContentObservable` | `ContentObservable` | Registry for ContentObservers. |
| `mExtras` | `Bundle` | Out-of-band metadata. |

## API Reference
*   `getCount()`: Abstract. Returns row count.
*   `getColumnNames()`: Abstract. Returns column names.
*   `getType(int)`: Returns type of column. Default `STRING`.
*   `moveToPosition(int)`: Moves cursor. Returns boolean success.
*   `registerContentObserver(ContentObserver)`: Adds observer.
*   `registerDataSetObserver(DataSetObserver)`: Adds observer.
*   `setNotificationUri(...)`: Sets up auto-notification.
*   `getExtras()`: Returns side-channel bundle.

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `abstract class` | `class` with pure virtual methods | `AbstractCursor` should be a base class. |
| `synchronized` | `std::mutex` / `std::lock_guard` | `mSelfObserverLock` needs a mutex. |
| `WeakReference` | `std::weak_ptr` | Used for `SelfContentObserver` to avoid cycles. |
| `CloseGuard` | `RAII` / Debug builds | C++ destructors handle cleanup; explicit leak tracking logic optional. |
| `ContentResolver` | Service Client | Interface to system content service. |
| `Bundle` | `AMessage` / `std::map` | Key-value store. |
| `Observable` | Signal/Slot or Callback List | Observer pattern implementation. |

## Test Cases & Validation
1.  **Navigation**: Create concrete subclass. Verify `moveToNext` increments `mPos`. Verify bounds checking (move to count -> false).
2.  **Observers**: Register mock observer. Call `onChange`. Verify observer notified.
3.  **Column Index**: Test `getColumnIndex` with "Col", "Table.Col" (should match), and "NonExistent" (return -1).
4.  **Lifecycle**: Call `close()`. Verify `isClosed()` is true and observers unregistered.

## Implementation Risks
*   **Thread Safety**: Java `Cursor` is not thread-safe, but `onChange` notifications happen on threads. `synchronized` blocks in `onChange` and notification registration must be preserved or equivalent mutexes used.
*   **Column Index Hack**: The specific logic handling "table.column" vs "column" in `getColumnIndex` must be replicated to maintain compatibility with sloppy SQL queries.
