# MatrixCursor - Reverse Engineering Documentation

## Executive Summary
`MatrixCursor` is a mutable, memory-resident implementation of `Cursor`. It stores data in a dynamic array of Objects. It is primarily used for testing, mocking, or creating small, temporary cursors programmatically without a backing database.

## Architecture Overview
*   **Inheritance**: `AbstractCursor`.
*   **Storage**: `Object[] data` (flattened 2D array).

## Detailed Functionality

### Data Storage
*   **Structure**: 1D array `data`.
*   **Indexing**: Row `i`, Column `j` is stored at `data[i * columnCount + j]`.
*   **Growth**: `ensureCapacity` expands array (doubling size) when adding rows.

### Row Construction
*   **newRow()**: Returns a `RowBuilder` fluent API.
*   **addRow(Object[])**: Adds a complete row. Validation checks column count.
*   **addRow(Iterable)**: Adds a row from iterable.

### Data Access
*   `get(int column)`: Retrieves object at `mPos * columnCount + column`. Checks bounds.
*   `getString`, `getInt`, etc.: Converts the stored Object using `toString()`, `Number.intValue()`, etc.
    *   *Note*: This performs runtime type conversion. A stored `Long` can be retrieved as `String` or `Int`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `data` | `Object[]` | Flattened data. |
| `rowCount` | `int` | Number of rows. |
| `columnCount` | `int` | Number of columns. |
| `columnNames` | `String[]` | Column names. |

## Java-to-C++ Translation Guide
*   **Data Structure**: `std::vector<std::vector<std::any>>` or a flattened `std::vector<std::any>` / `std::variant`.
*   **Type Safety**: Java uses `Object` and runtime checks. C++ needs a robust `Variant` type to handle String, Long, Double, Blob, Null.
*   **Validation**: Must enforce column count consistency on insertion.

## Test Cases
1.  **Builder**: `newRow().add(1).add("A")`. Verify data.
2.  **Conversion**: Store 1.5 (Double). `getInt()` -> 1. `getString()` -> "1.5".
3.  **Expansion**: Add more rows than initial capacity. Verify resize.
