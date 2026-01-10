# SearchView - Reverse Engineering Documentation

## Executive Summary
`SearchView` is a powerful widget that provides a search UI. It can exist as an icon that expands into a text field (`iconified`) or be permanently expanded. It handles query input, displays suggestions via an adapter, and dispatches search intents.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `SearchView`.
*   **Implements**: `CollapsibleActionView`.
*   **Key Components**:
    *   `SearchAutoComplete`: A custom `AutoCompleteTextView` for input.
    *   `SearchableInfo`: Configuration data (from system SearchManager).
    *   `SuggestionsAdapter`: `CursorAdapter` that fetches results from a content provider.

## Detailed Functionality

### 1. States
*   **Iconified**: Shows only a search icon.
*   **Expanded**: Shows the text field, submit button (optional), and close button.
*   **`updateViewsVisibility`**: Manages the visibility of the internal components (`mSearchButton`, `mSearchEditFrame`, etc.) based on state and text content.

### 2. Suggestions
*   Uses `SearchAutoComplete` to show a dropdown.
*   **`updateSearchAutoComplete`**: Configures the threshold, IME options, and adapter based on `SearchableInfo`.
*   **`launchSuggestion`**: When a suggestion is clicked, creates an Intent based on the cursor data (`SUGGEST_COLUMN_INTENT_ACTION`, etc.) and launches it.

### 3. Voice Search
*   If enabled in `SearchableInfo`, displays a microphone button.
*   Launches `RecognizerIntent` and handles the result (though the handling logic involves the activity).

## Java-to-C++ Translation Guide
*   **UI Composition**: It's a compound view. Construct the internal layout (plate, src_text, buttons) programmatically or via internal layout inflation.
*   **Intents**: The core logic revolves around creating and firing Android Intents (`ACTION_SEARCH`, `ACTION_VIEW`). This requires a strong abstraction for "Activity Launching".
*   **Database/Cursor**: The suggestion logic relies on `CursorAdapter` and Content Providers.

## Implementation Risks
*   **IME Interaction**: Managing soft keyboard visibility and focus when switching between iconified and expanded states is brittle.
*   **Cursor Management**: Asynchronous loading of suggestions is critical for performance; blocking the UI thread will cause jank.
