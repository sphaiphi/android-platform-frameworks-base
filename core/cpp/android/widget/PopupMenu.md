# PopupMenu - Reverse Engineering Documentation

## Executive Summary
`PopupMenu` is a helper class to show a modal menu anchored to a view. It encapsulates a `MenuBuilder`, `MenuPopupHelper`, and `MenuInflater`.

## Architecture Overview
*   **Role**: Menu Controller.
*   **Components**:
    *   `mMenu`: The menu data.
    *   `mPopup`: The helper that actually shows the window.

## Detailed Functionality
*   **Inflation**: `getMenuInflater().inflate(...)`.
*   **Events**: `OnMenuItemClickListener`.
*   **Drag-to-open**: Can attach a `ForwardingListener` to the anchor to support drag-to-open.

## Java-to-C++ Translation Guide
*   **Wrapper**: This is a high-level wrapper. Porting depends on the underlying Menu/Popup infrastructure.

## Implementation Risks
*   None.
