# SearchRecentSuggestions - Reverse Engineering Documentation

## Executive Summary
`SearchRecentSuggestions` is a utility to save and clear recent search queries in a `SearchRecentSuggestionsProvider`.

## Architecture Overview
- **Role**: Client Utility.
- **Dependencies**: `ContentResolver`.

## Detailed Functionality
-   **Save**: `saveRecentQuery` inserts the query into the provider (async via thread).
-   **Clear**: `clearHistory` deletes all rows.
-   **Truncate**: Limits history size (default 250).

## Data Model
-   **Columns**: `display1` (query), `display2` (optional line 2), `query`, `date`.

## Java-to-C++ Translation Guide
-   **Async**: C++ implementation should use a background thread/task for insertion to avoid blocking UI.
