# CrossProcessCursor - Reverse Engineering Documentation

## Executive Summary
`CrossProcessCursor` extends the `Cursor` interface to include methods specifically for inter-process communication (IPC) and `CursorWindow` management.

## API Reference
*   `getWindow()`: Returns the pre-filled `CursorWindow` if available.
*   `fillWindow(int position, CursorWindow window)`: Fills the provided window starting at `position`.
*   `onMove(int oldPosition, int newPosition)`: Notification of movement.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual class.
