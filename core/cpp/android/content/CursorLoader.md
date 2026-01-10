# CursorLoader - Reverse Engineering Documentation

## Executive Summary
`CursorLoader` is a specialized `AsyncTaskLoader` that queries a `ContentResolver` and returns a `Cursor`. It handles the lifecycle of the cursor (closing old ones) and monitoring for content changes to auto-reload.
**Note**: Deprecated in favor of AndroidX.

## Architecture Overview
-   **Inheritance:** Extends `AsyncTaskLoader<Cursor>`.
-   **Relationship:** Uses `ContentResolver.query`. Registers `ForceLoadContentObserver`.

## Detailed Functionality
-   **`loadInBackground()`**: Executes the query. Registers the observer.
-   **`deliverResult(Cursor)`**: Delivers the cursor to the client. Closes the old cursor if one existed.
-   **`onStartLoading()`**: Starts the load if content changed or no cursor exists.
-   **`onStopLoading()`**: Cancels load.
-   **`onReset()`**: Closes the cursor and stops loading.

## Data Model
-   `mUri`, `mProjection`, `mSelection`, `mSelectionArgs`, `mSortOrder`: Query arguments.
-   `mCursor`: Current cursor.
-   `mCancellationSignal`: For cancelling the query.

## API Reference
-   `public Cursor loadInBackground()`
-   `public void setUri(Uri uri)`
-   ... (Setters for query args)

## Java-to-C++ Translation Guide
-   **Loader**: Same as `AsyncTaskLoader`.
-   **Cursor**: Native cursor management.

## Implementation Risks
-   **Cursor Leaks**: Must ensure cursor is closed in `onReset` and when a new cursor is delivered.
