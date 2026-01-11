# BaseExpandableListAdapter - Reverse Engineering Documentation

## Executive Summary
`BaseExpandableListAdapter` is the base implementation for `ExpandableListAdapter`. It handles the observer pattern and ID generation for expandable lists (groups and children).

## Architecture Overview
*   **Type**: Abstract Class.
*   **Implements**: `ExpandableListAdapter`, `HeterogeneousExpandableList`.

## Detailed Functionality
*   **ID Generation**:
    *   `getCombinedGroupId`: `(groupId & 0x7FFFFFFF) << 32`.
    *   `getCombinedChildId`: ORs the group ID (high bits) with the child ID (low bits) and sets the 0th bit to 1.
    *   This logic ensures unique 64-bit IDs for every item in the flattened list.
*   **Observer Management**: Delegates to `DataSetObservable`.

## Java-to-C++ Translation Guide
*   **Bitwise Operations**: Replicate the ID generation logic exactly if compatibility with `ExpandableListView`'s flattening logic is required.

## Implementation Risks
*   **ID Collisions**: The default implementation assumes 32-bit integer IDs for groups/children.
