# ListPreference - Reverse Engineering Documentation

## Executive Summary
`ListPreference` allows the user to select one item from a list of choices presented in a dialog.

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `ListPreference` -> `DialogPreference`.
- **Storage**: Persists a single `String` value (from `entryValues`).

## Detailed Functionality
- **Entries vs. EntryValues**:
    -   `entries`: Human-readable text shown in the list.
    -   `entryValues`: Internal values persisted to storage.
-   **Dialog**: Uses `AlertDialog.Builder.setSingleChoiceItems`.
-   **Summary**: Can dynamically update summary to show the selected entry (using `%s` formatting).

## Data Model
-   `mEntries`: `CharSequence[]`
-   `mEntryValues`: `CharSequence[]`
-   `mValue`: `String`

## API Reference
-   `setEntries(...)`, `getEntries()`
-   `setEntryValues(...)`, `getEntryValues()`
-   `setValue(String)`, `getValue()`
-   `findIndexOfValue(String)`

## Java-to-C++ Translation Guide
-   **Arrays**: Map to `std::vector<std::string>` or similar.
-   **Index Matching**: Logic relies on parallel arrays for entries and values.

## Implementation Risks
-   **Array Mismatch**: `entries` and `entryValues` must have the same length.
