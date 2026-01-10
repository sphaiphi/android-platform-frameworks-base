# CursorWindow - Reverse Engineering Documentation

## Executive Summary
`CursorWindow` is a container for a result set of a cursor query. It is backed by shared memory (via native code), allowing it to be passed between processes (Binder IPC) efficiently. It is read-write locally but read-only remotely.

## Architecture Overview
*   **Inheritance**: `SQLiteClosable` -> `CursorWindow`.
*   **Implements**: `Parcelable`.
*   **Native Backing**: Heavy reliance on JNI methods (`nativeCreate`, `nativeGetLong`, etc.) mapping to C++ `android::CursorWindow`.

## Detailed Functionality

### Creation & Lifecycle
*   **Construction**:
    *   `CursorWindow(String name)`: Creates new window.
    *   `nativeCreate`: Allocates native window (shared memory).
*   **Destruction**:
    *   `dispose()`: Calls `nativeDispose` to release native resource.
    *   `finalize()`: Calls `dispose()`.
*   **IPC**:
    *   `writeToParcel`: Writes file descriptor/reference to Binder.
    *   `createFromParcel`: Reconstructs from Binder (maps shared memory).

### Row/Column Management
*   `setNumColumns(int)`: Must be called before adding rows.
*   `allocRow()`: Allocates space for a new row.
*   `freeLastRow()`: Rolls back allocation.
*   `clear()`: Resets data but keeps window open.
*   `getStartPosition()`: The row index in the full result set corresponding to the 0th row in this window.

### Data Access (Native Wrappers)
*   **Getters**: `getString`, `getLong`, `getDouble`, `getBlob`.
*   **Setters**: `putString`, `putLong`, `putDouble`, `putBlob`, `putNull`.
*   **Type**: `getType`.
*   **Logic**: All delegates to native methods. Pointers (`mWindowPtr`) passed to identify instance.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mWindowPtr` | `long` | Pointer to native C++ `CursorWindow` object. |
| `mStartPos` | `int` | Logical start position of this window in the cursor. |
| `mName` | `String` | Debug name. |
| `mCloseGuard` | `CloseGuard` | Leak detection. |

## Java-to-C++ Translation Guide
*   **Core**: This class is a JNI wrapper. The "Reverse Engineering" here is understanding that the *real* logic is already in C++ (`CursorWindow.cpp` / `.h`).
*   **Task**: The C++ implementation of the Android Framework Core likely *contains* the source for the native object this wraps. The C++ `android::database::CursorWindow` class needs to be exposed/implemented.
*   **Key Differences**: Java handles the `Parcelable` boilerplate; C++ handles the `Ashmem` (Anonymous Shared Memory).

## Test Cases & Validation
1.  **Allocation**: Create window, set columns, alloc row. Verify success.
2.  **Data Integrity**: Put string "test", get string. Verify match.
3.  **Overflow**: Try to allocate rows until full. Verify failure handling.
4.  **Parceling**: Write to parcel, read back. Verify data persists (simulates IPC).

## Implementation Risks
*   **Memory Leaks**: Failure to call `nativeDispose` leaks shared memory.
*   **Bounds**: Accessing row < 0 or > numRows must throw.
*   **Type Safety**: Getting a String from a Long column (and vice versa) behaves according to SQLite/Native rules (often loose typing/conversion).
