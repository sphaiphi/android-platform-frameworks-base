# BulkCursorDescriptor - Reverse Engineering Documentation

## Executive Summary
`BulkCursorDescriptor` is a container object used to pass all necessary initialization data for a `BulkCursorToCursorAdaptor` across processes. It bundles the binder interface, column names, row count, and an initial window.

## Architecture Overview
*   **Implements**: `Parcelable`.
*   **Role**: Data Transfer Object (DTO) for cursor initialization.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `cursor` | `IBulkCursor` | The Binder interface to the remote cursor. |
| `columnNames` | `String[]` | Projection / Column names. |
| `wantsAllOnMoveCalls` | `boolean` | Optimization flag. |
| `count` | `int` | Total row count. |
| `window` | `CursorWindow` | Initial data window (optimization to avoid immediate IPC roundtrip). |

## Java-to-C++ Translation Guide
*   **Structure**: A simple C++ struct or class with `readFromParcel` and `writeToParcel` methods.
*   **Parceling**: Order of fields in read/write must match Java exactly.
    1.  Strong Binder (`cursor`)
    2.  String Array (`columnNames`)
    3.  Int (`wantsAllOnMoveCalls`)
    4.  Int (`count`)
    5.  Int (Window flag: 1 if present, 0 if not)
    6.  Window (if present)
