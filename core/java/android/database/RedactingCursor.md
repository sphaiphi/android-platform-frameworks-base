# RedactingCursor - Reverse Engineering Documentation

## Executive Summary
`RedactingCursor` wraps an existing cursor and "redacts" (hides or replaces) specific columns with fixed values. It is useful for privacy or security when exposing internal cursors to external apps.

## Architecture Overview
*   **Inheritance**: `CrossProcessCursorWrapper`.
*   **Storage**: `SparseArray<Object> mRedactions` (Map of columnIndex -> redactedValue).

## Detailed Functionality
*   **Creation**: `create(Cursor, Map<String, Object> redactions)`. Maps column names to indices.
*   **Data Access**:
    *   `getString`, `getInt`, etc. check if `columnIndex` is in `mRedactions`.
    *   If yes, return stored value (cast to appropriate type).
    *   If no, call super.
*   **Window**: `fillWindow` is overridden to use `DatabaseUtils.cursorFillWindow` (iterating row-by-row) because the underlying `CursorWindow` cannot be returned directly (it contains unredacted data).

## Java-to-C++ Translation Guide
*   **Logic**: Proxy pattern with a map lookup on every access.
*   **Performance**: `fillWindow` fallback is slower than direct window passing.
