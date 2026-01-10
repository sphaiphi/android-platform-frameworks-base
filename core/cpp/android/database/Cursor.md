# Cursor - Reverse Engineering Documentation

## Executive Summary
`Cursor` is the primary interface for random read-write access to the result set of a database query. It abstracts the underlying storage mechanism (which could be SQLite, a ContentProvider, etc.). Implementations are not required to be synchronized.

## Architecture Overview
*   **Type**: Interface.
*   **Inheritance**: Extends `Closeable`.
*   **Implementations**: `AbstractCursor` (and its children), `CursorWrapper`.

## Detailed Functionality

### Constants (Field Types)
*   `FIELD_TYPE_NULL` (0)
*   `FIELD_TYPE_INTEGER` (1)
*   `FIELD_TYPE_FLOAT` (2)
*   `FIELD_TYPE_STRING` (3)
*   `FIELD_TYPE_BLOB` (4)

### Navigation
*   `getCount()`: Total rows.
*   `getPosition()`: Current index (-1 to count).
*   `move(int offset)`, `moveToPosition(int)`, `moveToFirst()`, `moveToLast()`, `moveToNext()`, `moveToPrevious()`: Movement.
*   `isFirst()`, `isLast()`, `isBeforeFirst()`, `isAfterLast()`: State.

### Data Access
*   `getColumnIndex(String)`: Get index by name.
*   `getColumnIndexOrThrow(String)`: Same, but throws.
*   `getColumnName(int)`: Get name by index.
*   `getColumnNames()`: Get all names.
*   `getColumnCount()`: Count.
*   `getBlob`, `getString`, `getShort`, `getInt`, `getLong`, `getFloat`, `getDouble`: Get value.
*   `getType(int)`: Get type.
*   `isNull(int)`: Null check.

### Extras & Observers
*   `getExtras()`, `setExtras()`: Out-of-band data.
*   `respond(Bundle)`: IPC communication.
*   `registerContentObserver`, `unregister...`: Data change listening.
*   `registerDataSetObserver`, `unregister...`: Cursor lifecycle listening.
*   `setNotificationUri`: URI to watch.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual abstract class in C++.
*   **Constants**: `enum class FieldType`.
*   **Annotations**: `IntRange`, `NonNull` imply contract checks in implementations.

## Test Cases & Validation
*   N/A (Interface definition). See `AbstractCursor` for implementation testing.
