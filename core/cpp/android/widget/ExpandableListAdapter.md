# ExpandableListAdapter - Reverse Engineering Documentation

## Executive Summary
`ExpandableListAdapter` is the interface for adapters that populate an `ExpandableListView`. It structures data into two levels: Groups and Children.

## Architecture Overview
*   **Type**: Interface.
*   **Hierarchy**: Similar to `Adapter` but 2D.

## API Contract
*   `getGroupCount()` / `getChildrenCount(groupPosition)`
*   `getGroup(groupPosition)` / `getChild(groupPosition, childPosition)`
*   `getGroupView(...)` / `getChildView(...)`: Returns views for the respective items.
*   `isChildSelectable(...)`
*   `onGroupExpanded` / `onGroupCollapsed`: Notifications.

## Java-to-C++ Translation Guide
*   **Abstract Base Class**: Implement as interface.

## Implementation Risks
*   None.
