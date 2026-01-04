# SimpleExpandableListAdapter - Reverse Engineering Documentation

## Executive Summary
`SimpleExpandableListAdapter` is an easy-to-use adapter for mapping static data (in the form of nested `List`s and `Map`s) to group and child views in an `ExpandableListView`. It simplifies the binding process by allowing developers to specify layout resources and data keys without subclassing.

## Architecture Overview
*   **Inheritance**: `BaseExpandableListAdapter` -> `SimpleExpandableListAdapter`.
*   **Data Structure**:
    *   **Group Data**: `List<Map<String, ?>>` (One map per group).
    *   **Child Data**: `List<List<Map<String, ?>>>` (Outer list for groups, inner list for children).

## Detailed Functionality
*   **Mapping**:
    *   `mGroupFrom`/`mGroupTo`: Maps keys in the group Map to TextView IDs in the group layout.
    *   `mChildFrom`/`mChildTo`: Maps keys in the child Map to TextView IDs in the child layout.
*   **Inflation**: Inflates `mExpandedGroupLayout`/`mCollapsedGroupLayout` for groups and `mChildLayout`/`mLastChildLayout` for children.
*   **Binding**: Iterates through the "to" array, finds views by ID, and sets their text using `data.get(from[i]).toString()`.

## Java-to-C++ Translation Guide
*   **Generic Collections**: Requires flexible container types (e.g., `std::vector` of `std::map<std::string, std::any>`).
*   **Binder**: Standard adapter binding pattern.

## Implementation Risks
*   **Data Integrity**: Requires the structure of the lists to strictly match (e.g., `mChildData.size() == mGroupData.size()`).
