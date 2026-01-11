# HeterogeneousExpandableList - Reverse Engineering Documentation

## Executive Summary
`HeterogeneousExpandableList` is an interface that allows `ExpandableListAdapter`s to define multiple view types for groups and children, enabling efficient view recycling for complex lists.

## Architecture Overview
*   **Type**: Interface.
*   **Methods**:
    *   `getGroupType(groupPosition)`
    *   `getChildType(groupPosition, childPosition)`
    *   `getGroupTypeCount()`
    *   `getChildTypeCount()`

## Java-to-C++ Translation Guide
*   **Virtual Methods**: Add these to the base `ExpandableListAdapter` class in C++.

## Implementation Risks
*   None.
