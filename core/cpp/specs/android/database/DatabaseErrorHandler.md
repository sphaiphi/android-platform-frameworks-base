# Database Error Handlers - Reverse Engineering Documentation

## Executive Summary
Defines the interface and default implementation for handling database corruption.

## Components

### DatabaseErrorHandler (Interface)
*   `onCorruption(SQLiteDatabase)`: Callback when corruption is detected.

### DefaultDatabaseErrorHandler
*   **Logic**:
    1.  Log error.
    2.  `wipeDetected`: Record the event.
    3.  `deleteDatabaseFile`: Deletes the DB file.
    4.  If attached databases exist, tries to delete them too.
    5.  Handles `.journal`, `.shm`, `.wal` files via `deleteDatabase`.

## Java-to-C++ Translation Guide
*   **File I/O**: Use C++ filesystem / POSIX APIs to delete files.
