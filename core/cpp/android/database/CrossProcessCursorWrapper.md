# CrossProcessCursorWrapper - Reverse Engineering Documentation

## Executive Summary
`CrossProcessCursorWrapper` adapts a standard `Cursor` to the `CrossProcessCursor` interface. If the wrapped cursor implements `CrossProcessCursor`, it delegates. If not, it provides a default implementation for `fillWindow` using iteration.

## Detailed Functionality
*   `fillWindow`:
    *   If wrapped is `CrossProcessCursor`: Delegate.
    *   Else: Call `DatabaseUtils.cursorFillWindow` (iterates cursor and puts data into window).
*   `getWindow`:
    *   If wrapped is `CrossProcessCursor`: Delegate.
    *   Else: Return `null`.

## Java-to-C++ Translation Guide
*   **Dynamic Cast**: Requires `dynamic_cast` or `instanceof` check to see if wrapped cursor supports the enhanced interface.
