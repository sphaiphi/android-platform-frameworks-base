# PopupWindow - Reverse Engineering Documentation

## Executive Summary
`PopupWindow` is a floating container that appears on top of the current activity. It is the fundamental building block for dropdowns, tooltips, and custom dialog-like overlays. It manages a `WindowManager.LayoutParams` and attaches a `PopupDecorView` to the WindowManager.

## Architecture Overview
*   **Role**: Floating Window Manager.
*   **Key Components**:
    *   `mContentView`: The view to display.
    *   `mDecorView`: Internal container (handles key dispatch, transitions).
    *   `mBackgroundView`: Holds the background drawable.
    *   `mWindowManager`: Used to add/update/remove the view.

## Detailed Functionality

### 1. Window Management
*   **`showAtLocation`**: Absolute positioning.
*   **`showAsDropDown`**: Positions relative to an anchor view.
*   **Layout Params**: Creates `WindowManager.LayoutParams` with type `TYPE_APPLICATION_PANEL` (typically).

### 2. Anchoring Logic
*   **`findDropDownPosition`**: Complex logic to keep the popup on screen.
    *   Calculates screen coordinates of the anchor.
    *   Checks if the popup fits below; if not, tries above.
    *   May resize the popup or scroll the parent to make room (`mAllowScrollingAnchorParent`).

### 3. Transitions
*   Supports `Transition` framework (enter/exit transitions) on the `mDecorView`.

### 4. Background
*   Wraps content in a `PopupBackgroundView` (FrameLayout) to render the background drawable and elevation shadow.

## Java-to-C++ Translation Guide
*   **Window System**: Requires integration with the OS window manager (creating a child window/layer).
*   **Math**: Logic for on-screen constraints and anchor positioning.

## Implementation Risks
*   **Leaking**: Failing to dismiss popups when the activity closes.
*   **Z-Order**: Managing elevation and overlap with other system windows (IME, status bar).
