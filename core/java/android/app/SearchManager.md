# SearchManager - Reverse Engineering Documentation

## Executive Summary
`SearchManager` provides access to system-level search services. It allows apps to launch the search UI (either local or global), manage search suggestions, and query information about searchable activities. It acts as a client-side wrapper for the `ISearchManager` AIDL interface and handles the lifecycle of the `SearchDialog`.

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.SEARCH_SERVICE`.
- **Core Components**:
    - `ISearchManager mService`: The AIDL proxy for system-level search logic.
    - `SearchDialog mSearchDialog`: The actual UI dialog managed by this instance.
- **Interfaces**: Implements `DialogInterface.OnDismissListener` and `DialogInterface.OnCancelListener` to coordinate dialog state with the application.

## Detailed Functionality

### Launching Search (`startSearch`)
**Purpose**: Displays the search interface to the user.
**Logic**: 
1. If `globalSearch` is true, it redirects to the system's global search activity (e.g., Google app).
2. Otherwise, it prepares and shows the local `SearchDialog`, configured for the providing activity.
3. Supports passing `app_data` bundles for contextual search.

### Suggestions Querying (`getSuggestions`)
**Purpose**: Retrieves matching results from a searchable app's content provider.
**Mechanism**: Constructs a `content://` URI using the authority and path from `SearchableInfo` and performs a standard `ContentResolver` query.

### Global Search
**Mechanism**:
- `getGlobalSearchActivities()`: Lists all apps that can handle platform-wide search.
- `getGlobalSearchActivity()`: Returns the current default global search provider.

### Assistant Integration
**Purpose**: Launching the system's assist activity (e.g., long-press home).
**Logic**: `launchAssist(Bundle args)` proxies the request to the `ISearchManager` to trigger the voice or visual assistant.

## API Reference (Key Methods)
- `public void startSearch(...)`: Shows search UI.
- `public void triggerSearch(...)`: Shows UI and executes query.
- `public SearchableInfo getSearchableInfo(...)`: Metadata lookup.
- `public Cursor getSuggestions(...)`: Fetches real-time suggestions.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use AIDL-generated C++ interface `android::app::ISearchManager`.
- **Dialog Management**: If a native C++ search UI is needed, it would be managed as a singleton window controlled by the manager.
- **Content Provider Query**: Use `android::content::ContentResolver` equivalents in C++ to perform suggestion queries.

## Implementation Risks
- **UI Mode Constraints**: Note that `SearchManager` is not supported in `UI_MODE_TYPE_WATCH`.
- **Permission Requirements**: Accessing search information or triggering certain intents may require `android.permission.GLOBAL_SEARCH`.
- **Death Handling**: If the system search service dies, the manager must be able to reconnect or handle `DeadSystemException`.
