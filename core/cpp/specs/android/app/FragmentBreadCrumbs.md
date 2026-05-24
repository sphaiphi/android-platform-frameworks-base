# FragmentBreadCrumbs - Reverse Engineering Documentation

## Executive Summary
`FragmentBreadCrumbs` is a deprecated UI widget that displays the FragmentManager's back stack as breadcrumbs.

## Architecture Overview
*   **Inheritance**: `ViewGroup`.
*   **Listener**: `FragmentManager.OnBackStackChangedListener`.

## Detailed Functionality
*   **Observation**: Listens to back stack changes.
*   **UI Construction**: Dynamically adds `TextViews` (and separators) for each back stack entry.
*   **Interaction**: Clicking a crumb pops the back stack to that state.

## Java-to-C++ Translation Guide
*   **Low Priority**: Deprecated.
*   **UI Construction**: Programmatic layout creation.

## Implementation Risks
*   None.
