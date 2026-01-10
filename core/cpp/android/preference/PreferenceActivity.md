# PreferenceActivity - Reverse Engineering Documentation

## Executive Summary
`PreferenceActivity` is a specialized Activity for displaying lists of preferences. It supports two modes:
1.  **Legacy**: Single list of preferences.
2.  **Modern (Headers + Fragments)**: A list of headers (categories) that launch specific `PreferenceFragment`s.

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `PreferenceActivity` -> `ListActivity`.
- **Multi-pane**: Supports dual-pane layout (Headers on left, Fragment on right) for large screens.

## Detailed Functionality
-   **Header Loading**: Loads headers from XML (`loadHeadersFromResource`) or programmatically.
-   **Fragment Management**: Switches fragments when headers are clicked.
-   **Legacy Support**: Can still host a `PreferenceManager` and show a `PreferenceScreen` directly (deprecated usage).
-   **Breadcrumbs**: Manages breadcrumbs for navigation.

## Data Model
-   `Header`: Inner class representing a section/header.

## API Reference
-   `onBuildHeaders(List<Header>)`: Subclasses override to populate headers.
-   `loadHeadersFromResource(int, List<Header>)`
-   `isValidFragment(String)`: Security check for fragment instantiation.

## Java-to-C++ Translation Guide
-   **Activity**: Map to the primary UI container/window controller.
-   **Headers**: List of struct/objects defining sections.

## Implementation Risks
-   **Fragment Injection**: `isValidFragment` was added to prevent security vulnerabilities where malicious intents could force the activity to instantiate arbitrary fragments.
