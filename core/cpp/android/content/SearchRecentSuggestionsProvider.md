# SearchRecentSuggestionsProvider - Reverse Engineering Documentation

## Executive Summary
`SearchRecentSuggestionsProvider` is a `ContentProvider` implementation that manages a database of recent search queries. It is designed to be subclassed by apps to quickly add search suggestion functionality.

## Architecture Overview
- **Inheritance:** Extends `ContentProvider`.
- **Database:** Uses `SQLiteOpenHelper` to manage a `suggestions.db` database.

## Detailed Functionality

### `setupSuggestions(String authority, int mode)`
**Purpose**: Configures the provider. Must be called in the constructor of the subclass.
**Algorithm**:
1. Sets authority and mode (queries vs 2-line display).
2. Configures `UriMatcher`.
3. Defines projection map for the suggestions table.

### `query`, `insert`, `delete`
**Purpose**: Standard provider operations backed by SQLite.
**Schema**: Table `suggestions` with columns `_id`, `display1`, `display2`, `query`, `date`.
**Query**: Supports matching against `display1` (and `display2`) using `LIKE`.

## Data Model
- `sDatabaseName`: "suggestions.db".
- `sSuggestions`: Table name.

## API Reference
- `protected void setupSuggestions(String authority, int mode)`

## Java-to-C++ Translation Guide
- **SQLite**: Direct mapping to C++ SQLite APIs.
- **ContentProvider**: Implements `IContentProvider` interface (via `ContentProviderNative` in C++).

## Implementation Risks
- **SQL Injection**: The class builds SQL strings. Ensure `selectionArgs` are used correctly (the code seems to do manual `LIKE` string construction which is risky if not careful, though here it validates inputs somewhat).
