# SearchDialog - Reverse Engineering Documentation

## Executive Summary
`SearchDialog` is a system-controlled UI component that displays the search interface for an application. It is managed by the `SearchManager` and provides a standard UI for entering queries, displaying suggestions, and triggering voice searches. It dynamically adjusts its behavior and appearance based on the `SearchableInfo` metadata of the active activity.

## Architecture Overview
- **Inheritance**: Extends `Dialog`.
- **Core Components**:
    - `SearchView mSearchView`: The primary widget for query entry.
    - `AutoCompleteTextView mSearchAutoComplete`: Handles suggestion display.
    - `ImageView mAppIcon`: Displays the icon of the app being searched.
    - `SearchableInfo mSearchable`: Metadata defining how search behaves for the target app.
- **Voice Search**: Integrates with the system recognizer via `RecognizerIntent`.

## Detailed Functionality

### Initialization (`show`)
**Purpose**: Prepares and displays the search interface.
**Algorithm**:
1. Queries `SearchManager` for `SearchableInfo` matching the launch component.
2. If available, creates the content view and configures the `SearchView`.
3. Updates UI elements (icon, badge, hints) based on metadata.
4. Handles landscape/portrait orientation adjustments.

### Suggestion Management
**Purpose**: Shows real-time results as the user types.
**Mechanism**: Uses the suggestion authority and path defined in `mSearchable` to query a content provider. selection and click events are handled via `OnSuggestionListener`.

### Query Execution (`launchQuerySearch`)
**Purpose**: Triggers the actual search action.
**Algorithm**:
1. Captures the text from the `SearchView`.
2. Constructs a `ACTION_SEARCH` intent.
3. Attaches `APP_DATA` and other metadata.
4. Starts the target activity and dismisses the dialog.

### UI Interaction
- `onTouchEvent`: Dismisses the dialog if the user taps outside the search plate.
- `onBackPressed`: Closes the dialog or the IME.
- `onConfigurationChanged`: Refreshes resources and layout when the device is rotated.

## API Reference
- `public boolean show(String initialQuery, ...)`: Main display trigger.
- `public void setWorking(boolean working)`: Shows/hides a progress spinner.
- `public void launchQuerySearch()`: Manually triggers search.

## Java-to-C++ Translation Guide
- **Dialog Framework**: Reimplement using a native C++ UI window or overlay.
- **SearchView**: Port the `SearchView` logic to a native C++ text input component with suggestion support.
- **Resource Loading**: Use `android::res::AssetManager` to load icons and localized strings for badges and hints.

## Implementation Risks
- **IME Interaction**: Handling soft keyboard visibility and "nm" (no microphone) options requires tight coordination with the `InputMethodManager`.
- **Suggestion Latency**: Queries to content providers can be slow. C++ implementation should handle suggestions asynchronously to keep the UI responsive.
- **Intent Security**: Ensure that the search intent targets the correct component and handles permissions for `APP_DATA`.
