# SearchUiService - Reverse Engineering Documentation

## Executive Summary
`SearchUiService` is an abstract base class for services that provide search results and handle the lifecycle of search sessions within the Android system. It allows apps to contribute to the global system search UI, processing queries and tracking user interactions with search targets.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ISearchUiService.Stub`.
*   **Session Management**: Uses `SearchSessionId` to maintain independent search contexts. It tracks active sessions and their associated callbacks in `mSessionEmptyQueryResultCallbacks`.
*   **Threading**: Dispatches all binder calls to the main thread via a `Handler`.
*   **Permission**: Requires `android.permission.MANAGE_SEARCH_UI`.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `ISearchUiService` binder interface.

### Session Lifecycle
*   **`onSearchSessionCreated(SearchContext, SearchSessionId)`**: Called when a new search session is initiated by a client (e.g., the launcher opening the search bar).
*   **`onDestroy(SearchSessionId)`**: Called when the session is closed and resources should be released.

### Query Handling
*   **`onQuery(SearchSessionId, Query, Consumer<List<SearchTarget>>)`**:
    *   **Goal**: Return results for a specific query string.
    *   **Parameters**:
        *   `Query`: Contains the search string and extras.
        *   `callback`: Consumer used to return a list of `SearchTarget` objects.
*   **Empty Query Updates**: Supports "zero-state" suggestions (results shown before the user types). The service can proactively push updates via `updateEmptyQueryResult`.

### Interaction Tracking
*   **`onNotifyEvent(SearchSessionId, Query, SearchTargetEvent)`**: Notifies the service about user actions like tapping a result, long-pressing, or the search UI being shown/hidden.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.search.SearchUiService"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ISearchUiService.Stub`.
*   **C++**: `BnSearchUiService`.

### Data Model
*   `SearchContext`, `Query`, `SearchTarget`, `SearchTargetEvent` are all Parcelables.
*   `SearchTarget` is a complex object containing text, icons, and action intents.

### Performance
*   Search results must be returned with very low latency to maintain a fluid user experience. Heavy search indexing should be performed in a separate process or worker thread.

## Implementation Risks
*   **Resource Leaks**: Callbacks must be properly unregistered upon session destruction or binder death. The Java implementation uses `linkToDeath`.
*   **Privacy**: Search queries contain highly sensitive personal information. The service must handle queries according to strict privacy guidelines.
