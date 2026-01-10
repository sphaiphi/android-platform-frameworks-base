# SuggestionsAdapter - Reverse Engineering Documentation

## Executive Summary
`SuggestionsAdapter` is a specialized `ResourceCursorAdapter` used by `SearchView` to display search suggestions backed by a Content Provider. It handles the complexity of mapping various suggestion columns (text, icon, intent data) to the views in the suggestion dropdown.

## Architecture Overview
*   **Inheritance**: `ResourceCursorAdapter` -> `SuggestionsAdapter`.
*   **Role**: Data Binder for Search.
*   **Dependencies**: `SearchManager` constants (`SUGGEST_COLUMN_TEXT_1`, etc.).

## Detailed Functionality

### 1. Querying
*   **`runQueryOnBackgroundThread`**: Calls `mSearchManager.getSuggestions`. This abstracts the cross-process call to the suggestion provider.
*   **Refinement**: Handles the "commit icon" (arrow) which copies text to the query box without submitting (`REFINE_BY_ENTRY`).

### 2. View Binding
*   **Cache**: `ChildViewCache` (ViewHolder pattern).
*   **Columns**: Dynamically resolves column indices (`mText1Col`, `mIconName1Col`) from the cursor.
*   **Logic**:
    *   Text: Sets text1 and text2. Handles HTML formatting / URL coloring.
    *   Icons: Loads drawables from Resources, URIs, or Content Providers (`getDrawableFromResourceValue`). Caches them.

## Java-to-C++ Translation Guide
*   **Content Provider**: Depends entirely on the Android `Cursor` and `ContentResolver` model.
*   **Resources**: Extensive logic to resolve resources across packages (loading an icon from the target app's package).

## Implementation Risks
*   **Performance**: Loading icons from other processes/files on the UI thread (in `bindView`) causes scrolling lag. Ideally should be async.
*   **Security**: Loading remote resources/URIs.
