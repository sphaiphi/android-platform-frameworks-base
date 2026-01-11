# Entity - Reverse Engineering Documentation

## Executive Summary
`Entity` represents a data item consisting of a top-level `ContentValues` map and a list of sub-values (related data), each also a `ContentValues` map associated with a URI.

## Architecture Overview
-   **Usage:** Used in `EntityIterator` for bulk data processing (e.g., Contacts).

## Detailed Functionality
-   **`Entity(ContentValues values)`**: Constructor.
-   **`addSubValue(Uri uri, ContentValues values)`**: Adds a sub-value.

## Data Model
-   `mValues`: `ContentValues` (Main values).
-   `mSubValues`: `ArrayList<NamedContentValues>`.

## Inner Class `NamedContentValues`
-   `uri`: `Uri`.
-   `values`: `ContentValues`.

## API Reference
-   `public ContentValues getEntityValues()`
-   `public ArrayList<NamedContentValues> getSubValues()`

## Java-to-C++ Translation Guide
-   **Structure**: A struct or class holding the main map and a vector of sub-structs.

## Implementation Risks
-   None.
