# MultiCheckPreference - Reverse Engineering Documentation

## Executive Summary
`MultiCheckPreference` allows the user to toggle multiple items on/off from a list.

**Note:** This class is deprecated and hidden.

## Architecture Overview
- **Inheritance**: `MultiCheckPreference` -> `DialogPreference`.
- **Storage**: Persists `boolean[]` state (internally, the persistence mechanism for this specific class seems custom or limited compared to `MultiSelectListPreference`).

## Detailed Functionality
-   **Dialog**: Uses `AlertDialog.Builder.setMultiChoiceItems`.
-   **State**: Maintains an array of booleans (`mSetValues`) corresponding to entries.

## Data Model
-   `mEntries`: `CharSequence[]`
-   `mEntryValues`: `String[]`
-   `mSetValues`: `boolean[]`

## API Reference
-   `setEntries(...)`
-   `setEntryValues(...)`
-   `setValues(boolean[])`, `getValues()`

## Java-to-C++ Translation Guide
-   **Obsolete**: This class is largely superseded by `MultiSelectListPreference` which persists a `Set<String>`.

## Implementation Risks
-   **Persistence**: The standard `Preference` persistence methods (`persistBoolean`, `persistString`) don't naturally support `boolean[]`. This class might rely on manual handling or be less functional.
