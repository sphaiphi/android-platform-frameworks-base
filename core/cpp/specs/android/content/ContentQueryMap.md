# ContentQueryMap - Reverse Engineering Documentation

## Executive Summary
`ContentQueryMap` caches the contents of a `Cursor` into a `Map` of `ContentValues`, indexed by a specific column. It can optionally observe the cursor's content provider for changes and auto-requery.

## Architecture Overview
- **Inheritance:** Extends `Observable`.
- **Relationship:** Wraps a `Cursor`.

## Detailed Functionality

### `ContentQueryMap(Cursor, String, boolean, Handler)`
**Purpose**: Constructor.
**Algorithm**:
1. Reads the cursor into `mValues` map.
2. If `keepUpdated` is true, registers a `ContentObserver`.

### `requery()`
**Purpose**: Refreshes data.
**Algorithm**: Calls `cursor.requery()`, clears cache, and re-reads cursor.

### `readCursorIntoCache(Cursor)`
**Purpose**: Iterates cursor and populates map.
**Algorithm**: Loops `cursor.moveToNext()`, creates `ContentValues` for each row, puts in map keyed by the specified column.

## Data Model
- `mCursor`: `Cursor`.
- `mValues`: `Map<String, ContentValues>`.
- `mKeyColumn`: `int`.

## API Reference
- `public ContentValues getValues(String rowName)`
- `public void requery()`
- `public void close()`

## Java-to-C++ Translation Guide
- **Cursor**: Requires native Cursor interface.
- **ContentObserver**: Native `IContentObserver`.
- **Map**: `std::map`.

## Implementation Risks
- **Memory**: Caching an entire cursor in memory can be expensive.
- **Performance**: Requerying on main thread (implied if used directly) can stutter.
