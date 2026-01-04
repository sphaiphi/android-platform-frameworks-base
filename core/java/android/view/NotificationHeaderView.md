# NotificationHeaderView - Reverse Engineering Documentation

## Executive Summary
`NotificationHeaderView` is a specialized `RelativeLayout` that forms the top part of a standard system notification. It contains the app icon, app name, timestamps, and the expand/collapse button. it includes custom touch logic to ensure the entire header area is responsive to expand gestures.

## Architecture Overview
*   **Role**: UI container for notification metadata.
*   **Interaction**: Handles complex touch regions (`HeaderTouchListener`) where multiple small views (icon, button) need to trigger a single "Expand" action.

## Detailed Functionality

### 1. Child Management
*   Automatically identifies and links to standard IDs: `icon`, `expand_button`, `notification_top_line`.

### 2. Custom Touch Handling
*   **`HeaderTouchListener`**: Maps a "touchable height" area across the entire width of the header. It ensures that taps near the app name or icon are still routed to the expand logic.

### 3. Visual Styling
*   **`styleTextAsTitle()`**: Swaps text appearances for different notification priorities.
*   **`centerTopLine()`**: Dynamically adjusts layout parameters to vertically center the content based on redesign flags.

## Java-to-C++ Translation Guide
*   **Pattern**: Custom Layout.
*   **Touch Regions**: Requires implementation of a hit-test list (`ArrayList<Rect>`).

## Implementation Risks
*   **Nested Clipping**: The header often uses `setClipToPadding(false)` to allow shadows or badges to bleed into the margins; ensure the C++ renderer respects this.
*   **RemoteViews**: This view is marked with `@RemoteView`, meaning it must support serialization and remote invocation of its methods (e.g., via `setTopLineExtraMarginEndDp`).
