# PreferenceScreen - Reverse Engineering Documentation

## Executive Summary
`PreferenceScreen` is a specialized `PreferenceGroup` that represents a root of the preference hierarchy or a sub-screen.

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `PreferenceScreen` -> `PreferenceGroup`.
- **Role**: Root node or Sub-screen.

## Detailed Functionality
-   **Root**: When attached to an Activity, acts as the invisible root.
-   **Navigation**: When nested, clicking it opens a **Dialog** containing the sub-preferences (or starts an intent).
-   **Adapter Creation**: Creates the `PreferenceGroupAdapter` used to display its children.
-   **Binding**: `bind(ListView)` attaches the adapter to the list.

## Data Model
-   `mRootAdapter`: The adapter for the list.
-   `mDialog`: The dialog used for sub-screens.

## API Reference
-   `getRootAdapter()`
-   `bind(ListView)`
-   `getDialog()`

## Java-to-C++ Translation Guide
-   **Navigation Logic**: The decision to show a dialog or new screen is key.
-   **View Binding**: Connecting the data tree to the list view.
