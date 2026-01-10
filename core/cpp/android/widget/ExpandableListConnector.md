# ExpandableListConnector - Reverse Engineering Documentation

## Executive Summary
`ExpandableListConnector` is a `BaseAdapter` that acts as a bridge/proxy. It flattens the 2D data of an `ExpandableListAdapter` into a 1D list that a standard `ListView` can display.

## Architecture Overview
*   **Inheritance**: `BaseAdapter` -> `ExpandableListConnector`.
*   **Role**: Adapter Flattener / State Manager.
*   **Key Data**: `mExpGroupMetadataList` (List of currently expanded groups and their cached flat positions).

## Detailed Functionality

### 1. Flattening Logic
*   **Conceptual Model**: The list is a sequence of Groups. If a Group is expanded, its Children follow immediately after it.
*   **`getCount`**: Sum of all groups + sum of children of *expanded* groups.
*   **`getItem`/`getView`**:
    *   Determines if the flat position corresponds to a Group or a Child.
    *   Delegates to the underlying `ExpandableListAdapter`.

### 2. Position Translation
*   **`getUnflattenedPos`**: Converts a flat list position to a `PositionMetadata` (Group Index, Child Index, Type). Uses binary search on `mExpGroupMetadataList`.
*   **`getFlattenedPos`**: Converts Group/Child index back to flat position.

### 3. Expansion State
*   **`expandGroup`**: Adds group metadata to `mExpGroupMetadataList`, notifies data change.
*   **`collapseGroup`**: Removes metadata, notifies data change.

## Java-to-C++ Translation Guide
*   **Metadata**: This is the core. The connector maintains a sparse list of *expanded* items.
*   **Algorithms**: The binary search logic for position translation must be exact.

## Implementation Risks
*   **Index Errors**: Off-by-one errors in mapping flat positions to group/child indices are common and fatal.
