# ActivityChooserView - Reverse Engineering Documentation

## Executive Summary
`ActivityChooserView` is a widget that allows users to choose an activity to handle an intent. It typically appears as a "Share" action in an ActionBar. It displays the default (most used) activity as a button and an "expand" button that opens a popup list of other options.

## Architecture Overview
*   **Inheritance**: `ViewGroup` (extends `ViewGroup`, typically acts like a `LinearLayout`).
*   **Components**:
    *   `mDefaultActivityButton`: Button for the top-ranked activity.
    *   `mExpandActivityOverflowButton`: Opens the full list.
    *   `mAdapter`: `ActivityChooserViewAdapter` (Internal).
    *   `mListPopupWindow`: The dropdown menu.

## Detailed Functionality

### 1. Interaction Modes
*   **Default Action**: Clicking the icon directly launches the top activity.
*   **Overflow**: Clicking the arrow/expand button shows the `ListPopupWindow`.

### 2. Data Binding
*   Connects to `ActivityChooserModel`.
*   Observes data changes to update the default icon and list contents.

### 3. Measurement
*   Calculates width based on the content. Can be collapsed (just icon) or expanded.

## Java-to-C++ Translation Guide
*   **Popup**: Relies on `ListPopupWindow`. Needs a C++ equivalent for dropdown menus.
*   **Adapter**: Internal adapter maps the `ActivityChooserModel` data to list items (Icon + Label).

## Implementation Risks
*   **Accessibility**: Needs proper content descriptions for the separate buttons (Default vs Expand).
