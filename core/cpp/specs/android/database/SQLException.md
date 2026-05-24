# Exceptions - Reverse Engineering Documentation

## Executive Summary
A collection of RuntimeExceptions specific to database operations.

## Classes
*   `SQLException`: Base class.
*   `CursorIndexOutOfBoundsException`: Index out of valid range.
*   `StaleDataException`: Accessing closed/invalidated cursor.
*   `SQLiteException`: Native SQLite error (mapped from error code).
    *   Subclasses: `SQLiteConstraintException`, `SQLiteDiskIOException`, `SQLiteFullException`, etc.

## Java-to-C++ Translation Guide
*   **Inheritance**: Define a `SQLException` base class inheriting from `std::runtime_error` or `std::exception`.
*   **Mapping**: SQLite error codes (returned by `sqlite3_step` etc.) should be thrown as specific C++ exception subclasses to match Java semantics.
