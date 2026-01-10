# ListView - Reverse Engineering Documentation

## Executive Summary
`ListView` is the classic scrolling list widget in Android. It displays a vertically scrollable collection of views provided by a `ListAdapter`. It supports headers, footers, dividers, and various selection modes.

## Architecture Overview
*   **Inheritance**: `AbsListView` -> `ListView`.
*   **Role**: Vertical List.
*   **Key Data**: `mHeaderViewInfos`, `mFooterViewInfos` (Lists of fixed views).

## Detailed Functionality

### 1. Measurement
*   **`measureHeightOfChildren`**: helper to determine height (used for `WRAP_CONTENT`).
*   Respects `mDividerHeight`.

### 2. Layout (`layoutChildren`)
*   **Fill Strategies**:
    *   `fillFromTop`: Start from top, fill down.
    *   `fillFromBottom`: Start from bottom (stackFromBottom), fill up.
    *   `fillFromSelection`: Start from selected item, fill up and down.
    *   `fillSpecific`: Start from specific position.
*   **Fixed Views**: Headers/Footers are treated specially; they are not recycled in the same way as adapter views.

### 3. Interaction
*   **Arrow Scrolling**: Handles D-pad navigation (`arrowScroll`).
*   **Focus**: Supports internal focus (`itemsCanFocus`).

## Java-to-C++ Translation Guide
*   **Logic**: The `layoutChildren` method is a massive state machine handling all combinations of data change, focus change, and scroll position. It needs careful porting.
*   **Optimization**: Ensure `RecycleBin` usage matches the Java implementation to maintain performance.

## Implementation Risks
*   **Header/Footer Wrapping**: When headers are added, the adapter is wrapped in `HeaderViewListAdapter`. This changes indices (off-by-N).
*   **Focus Management**: Managing focus within list items (e.g., buttons inside rows) is complex.
