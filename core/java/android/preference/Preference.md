# Preference - Reverse Engineering Documentation

## Executive Summary
`Preference` is the base building block for the preference UI. It represents a single setting item that can be displayed, clicked, and persisted. It manages its own state, persistence key, title, summary, and icon.

**Note:** This class is deprecated.

## Architecture Overview
- **Role**: Base Class / Component.
- **Persistence**: Interfaces with `SharedPreferences` (via `PreferenceManager`) or a custom `PreferenceDataStore`.
- **UI**: Inflates a layout (`mLayoutResId`) and binds data to views (Title, Summary, Icon).

## Detailed Functionality
1.  **Inflation**: Constructed from XML attributes.
2.  **Hierarchy**: Can be part of a `PreferenceGroup`.
3.  **Persistence**:
    -   `persistInt`, `persistString`, etc. save values.
    -   `getPersistedInt`, etc. retrieve values.
    -   Handles default values (`setDefaultValue`, `onSetInitialValue`).
4.  **Interaction**:
    -   `onClick()`
    -   `OnPreferenceClickListener`
    -   `OnPreferenceChangeListener` (for value validation).
5.  **Dependency**: Can depend on another preference (`dependency` key), disabling itself if the dependency is not met.

## Data Model
-   `mKey`: Unique key for persistence.
-   `mTitle`, `mSummary`: Display text.
-   `mOrder`: Sort order.
-   `mDefaultValue`: Initial value.
-   `mEnabled`, `mSelectable`: State flags.

## API Reference
-   `setKey(String)`, `getKey()`
-   `setTitle(...)`, `setSummary(...)`
-   `setDefaultValue(Object)`
-   `setOnPreferenceChangeListener(...)`
-   `setOnPreferenceClickListener(...)`
-   `persistString(String)`, `getPersistedString(String)` (and other types)

## Java-to-C++ Translation Guide
-   **Base Class**: This should be the root class of the C++ preference hierarchy.
-   **Persistence Abstraction**: Abstract the storage mechanism (SharedPreferences) so it can be swapped.
-   **View Binding**: The `onBindView` pattern is central to updating the UI.

## Implementation Risks
-   **Dependency Cycles**: The dependency logic (`registerDependent`) must handle potential cycles or invalid keys gracefully.
-   **Persistence Sync**: Ensuring in-memory state matches persisted state is complex (`onSetInitialValue`).
