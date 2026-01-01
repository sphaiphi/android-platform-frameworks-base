# DatabaseUtils - Reverse Engineering Documentation

## Executive Summary
`DatabaseUtils` is a collection of static utility methods for database operations. It covers SQL statement analysis, data binding, cursor debugging/dumping, and string escaping.

## Detailed Functionality

### SQL Analysis
*   `getSqlStatementType(String sql)`: returns type (SELECT, UPDATE, etc.) by checking the first few non-whitespace characters.
*   `getSqlStatementTypeExtended`: More granular types.

### Binding & Escaping
*   `sqlEscapeString(String)`: Adds single quotes and escapes internal quotes (`'` -> `''`).
*   `appendEscapedSQLString`: Appends to builder.
*   `bindObjectToProgram`: Binds Java objects to `SQLiteProgram` using type checking.

### Cursor Utilities
*   `dumpCursor`: Prints entire cursor to log/stream.
*   `cursorFillWindow`: Fills a `CursorWindow` from a `Cursor`. (Critical fallback for cursors that don't support windows natively).
*   `queryNumEntries`: Runs `SELECT count(*)`.

### Helpers
*   `longForQuery`, `stringForQuery`: Executors for 1x1 result queries.
*   `InsertHelper` (Deprecated): Optimized bulk insert (avoids recompling SQL).

## Java-to-C++ Translation Guide
*   **Parsing**: Replicate the prefix-stripping logic for statement type detection to match Android behavior.
*   **Debug**: `dumpCursor` is very useful for C++ logging.
*   **String Handling**: Requires robust UTF-8 string manipulation for escaping.
