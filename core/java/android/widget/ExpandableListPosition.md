# ExpandableListPosition - Reverse Engineering Documentation

## Executive Summary
`ExpandableListPosition` is a helper value class representing a position in an expandable list. It stores the type (`GROUP` or `CHILD`), the group position, the child position, and optionally the flat list position.

## Architecture Overview
*   **Role**: Data Struct / Value Object.
*   **Pooling**: Uses a static pool (`sPool`) to reduce object allocation churn.

## Detailed Functionality
*   **Fields**: `groupPos`, `childPos`, `flatListPos`, `type`.
*   **Packing**: Can convert to/from a packed 64-bit long representation (used by `ExpandableListView`'s public API).

## Java-to-C++ Translation Guide
*   **Struct**: Simple struct.
*   **Pooling**: Not needed in C++ if allocated on stack or passed by value.

## Implementation Risks
*   None.
