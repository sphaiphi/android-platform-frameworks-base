# SimpleCursorAdapter - Reverse Engineering Documentation

## Executive Summary
`SimpleCursorAdapter` is an adapter that maps columns from a `Cursor` to `TextView`s or `ImageView`s in an XML layout. It is the cursor-backed equivalent of `SimpleAdapter`.

## Architecture Overview
*   **Inheritance**: `ResourceCursorAdapter` -> `SimpleCursorAdapter`.

## Detailed Functionality
*   **Mapping**: `mFrom` (column indices) -> `mTo` (view IDs).
*   **Binding (`bindView`)**:
    *   Reads string from cursor column.
    *   Uses `ViewBinder` if present.
    *   Else, sets text or image similar to `SimpleAdapter`.
*   **String Conversion**: Supports `CursorToStringConverter` for `AutoCompleteTextView` filtering.

## Java-to-C++ Translation Guide
*   **Database**: Depends on `Cursor` abstraction.

## Implementation Risks
*   **Performance**: Repeated `findViewById` in `bindView` (though usually cached by the ViewHolder pattern in modern practice, this class is old-school).
