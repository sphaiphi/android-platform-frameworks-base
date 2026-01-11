# ExpandableListView - Reverse Engineering Documentation

## Executive Summary
`ExpandableListView` is a view that shows items in a vertically scrolling two-level list (groups and children). It extends `ListView` and uses `ExpandableListConnector` to flatten the hierarchy.

## Architecture Overview
*   **Inheritance**: `ListView` -> `ExpandableListView`.
*   **Key Components**:
    *   `mConnector`: The adapter that flattens the data.
    *   `mAdapter`: The user-provided `ExpandableListAdapter`.

## Detailed Functionality

### 1. Adapter Management
*   Wraps the user's `ExpandableListAdapter` in an `ExpandableListConnector`.
*   Sets the connector as the `ListView`'s adapter.

### 2. Interaction
*   **Group Click**: Toggles expansion/collapse (unless handled by a listener).
*   **Drawing**: Draws specific indicators (arrows) next to groups to show expansion state.
    *   `mGroupIndicator`, `mChildIndicator`.
*   **ContextMenu**: Handles packed position info for context menus.

### 3. Drawing Indicators (`dispatchDraw`)
*   Iterates over visible items.
*   Asks the connector for the type (Group/Child).
*   Draws the appropriate indicator drawable in the specified bounds (left/right).

## Java-to-C++ Translation Guide
*   **Decoration**: Requires logic to draw overlays (indicators) on top of the list items.
*   **Event Interception**: Intercepts item clicks to handle group expansion logic before dispatching to listeners.

## Implementation Risks
*   **State Sync**: Ensuring the connector's state matches the visual state.
