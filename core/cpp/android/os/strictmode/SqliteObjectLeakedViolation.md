# SqliteObjectLeakedViolation - Reverse Engineering Documentation

## Executive Summary
`SqliteObjectLeakedViolation` is a specialized version of a leak violation, specifically for SQLite databases or cursors that were not closed before being finalized.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Payload**: Includes an `originStack` capturing where the SQLite object was opened.
