# HeaderViewListAdapter - Reverse Engineering Documentation

## Executive Summary
`HeaderViewListAdapter` is a wrapper adapter used by `ListView` when header or footer views are added. It wraps the user-provided adapter and injects the fixed header/footer views at the beginning/end of the list.

## Architecture Overview
*   **Inheritance**: `WrapperListAdapter`.
*   **Implements**: `Filterable`.
*   **State**: `ArrayList<FixedViewInfo>` for headers and footers.

## Detailed Functionality
*   **`getCount`**: `headers + adapter.count + footers`.
*   **`getItem` / `getView`**:
    *   If pos < numHeaders: Return header.
    *   If pos < numHeaders + adapterCount: Delegate to adapter.
    *   Else: Return footer.
*   **`areAllItemsEnabled`**: False if any header/footer is not selectable.

## Java-to-C++ Translation Guide
*   **Composition**: Standard adapter wrapping pattern.

## Implementation Risks
*   **View Types**: Headers/Footers are usually treated as `ITEM_VIEW_TYPE_HEADER_OR_FOOTER` (special constant), meaning they aren't recycled in the standard pool.
