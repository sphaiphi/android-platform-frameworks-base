# AbstractWindowedCursor - Reverse Engineering Documentation

## Executive Summary
`AbstractWindowedCursor` extends `AbstractCursor` to provide support for cursors backed by a `CursorWindow`. A `CursorWindow` is a shared memory buffer containing a batch of rows. This class manages the lifecycle and ownership of this window and implements the data retrieval methods by querying the window.

## Architecture Overview
*   **Inheritance**: `AbstractCursor` -> `AbstractWindowedCursor`.
*   **Ownership**: Strictly owns a `CursorWindow`.
*   **Relationship**: Bridges the abstract `Cursor` API to the concrete `CursorWindow` storage.

## Detailed Functionality

### Window Management
*   **Purpose**: Manages the `CursorWindow` holding data.
*   **Logic**:
    *   `mWindow`: The active window.
    *   `setWindow(CursorWindow)`: Closes old window, assigns new one.
    *   `hasWindow()`: Null check.
    *   `close()` / `onDeactivateOrClose()`: Closes the window to free shared memory.
    *   `clearOrCreateWindow()`: Helper to reset or create window.

### Data Retrieval
*   **Purpose**: Implements abstract getters using the window.
*   **Methods**:
    *   `getString(int)`, `getInt(int)`, `getBlob(int)`, etc.:
        1.  Calls `checkPosition()`.
        2.  Delegates to `mWindow.getX(mPos, columnIndex)`.
*   **Type Inspection**:
    *   `getType(int)`: Delegates to `mWindow.getType(mPos, columnIndex)`.
    *   `isNull(int)`: Checks if type is `FIELD_TYPE_NULL`.

### Position Checks
*   **Override**: `checkPosition()`.
*   **Logic**: Calls super. If `mWindow` is null, throws `StaleDataException`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mWindow` | `CursorWindow` | The shared memory buffer. Nullable. |

## API Reference
*   `getWindow()`: Returns the underlying `CursorWindow`.
*   `setWindow(CursorWindow)`: Sets the window.
*   `hasWindow()`: Checks existence.
*   `getBlob`, `getString`, `copyStringToBuffer`, `getShort`, `getInt`, `getLong`, `getFloat`, `getDouble`, `isNull`, `getType`: Implemented using `mWindow`.

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `CursorWindow` | `android::CursorWindow` | Native C++ class exists. |
| `StaleDataException` | `std::runtime_error` | Specific error type needed. |
| `checkPosition` | Member function | Ensure bounds and window validity. |

## Test Cases & Validation
1.  **Window Access**: `setWindow`, then `getString`. Verify data retrieved from window.
2.  **Stale Data**: `close()`, then try `getString`. Should throw exception.
3.  **Ownership**: `setWindow(w2)` should `close()` `w1`.

## Implementation Risks
*   **Lifetime**: Critical to ensure `CursorWindow` is closed exactly once when the cursor is closed or window replaced to avoid shmem leaks.
*   **Null Window**: `checkPosition` logic must rigorously check for null `mWindow`.
