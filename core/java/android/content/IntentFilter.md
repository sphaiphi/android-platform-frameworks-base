# IntentFilter - Reverse Engineering Documentation

## Executive Summary
`IntentFilter` is a structured description of Intent values to be matched. It matches against actions, categories, and data (type, scheme, authority, path) in an Intent. It is used to declare what intents a component (Activity, Service, BroadcastReceiver) can handle.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Purpose:** Matching Intents against components. Used in `AndroidManifest.xml` and dynamic receiver registration.

## Detailed Functionality

### Matching Rules
The filter matches an Intent if:
1.  **Action**: The Intent's action matches one of the filter's actions (or the filter has no actions and the intent has no action - wait, no, if filter has no actions it blocks all intents).
2.  **Categories**: The Intent's categories are a *subset* of the filter's categories.
3.  **Data**: The Intent's data (URI and Type) matches the filter's data specifications.

### Data Matching
Data matching involves:
-   **Type**: MIME type matching (supports wildcards like `image/*`).
-   **Scheme**: URI scheme (e.g., `http`, `content`).
-   **Authority**: Host and port.
-   **Path**: Path, prefix, or pattern (glob/advanced glob).
-   **Scheme Specific Part (SSP)**: For hierarchical URIs.

### `match(...)` Method
**Purpose**: The core logic for testing if an Intent matches the filter.
**Returns**: An integer indicating the match quality (category and adjustment) or a negative error code (e.g., `NO_MATCH_ACTION`).

### XML Serialization
-   **`writeToXml` / `readFromXml`**: Serializes the filter to/from XML, used for persistent settings (like preferred activities).

## Data Model
-   `mActions`: `ArraySet<String>`.
-   `mCategories`: `ArrayList<String>`.
-   `mDataSchemes`, `mDataTypes`, `mDataAuthorities`, `mDataPaths`, etc.: Lists of data properties.
-   `mPriority`: `int` - Priority of the filter.

## API Reference
-   `public final void addAction(String action)`
-   `public final void addDataType(String type)`
-   `public final void addDataScheme(String scheme)`
-   `public final int match(ContentResolver resolver, Intent intent, boolean resolve, String logTag)`

## Java-to-C++ Translation Guide
-   **Parcelable**: Standard.
-   **Matching Logic**: The `match` method contains complex logic that must be replicated exactly for correct intent resolution in C++.
-   **String Handling**: MIME type and scheme matching is case-sensitive in Android framework (implementation detail in `IntentFilter`), unlike RFCs. C++ implementation must respect this.

## Implementation Risks
-   **Matching Complexity**: The interaction between type, scheme, and the "wildcards" in filters is subtle.
-   **Performance**: Intent matching is a hot path.
