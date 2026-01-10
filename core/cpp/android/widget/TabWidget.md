# TabWidget - Reverse Engineering Documentation

## Executive Summary
`TabWidget` is a horizontal `LinearLayout` that displays the tab indicators for a `TabHost`. It draws a bottom strip (selection indicator) and dividers.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `TabWidget`.
*   **Role**: Tab Strip.

## Detailed Functionality

### 1. Layout
*   **Imposed Widths**: `measureHorizontal` logic attempts to distribute extra width among tabs if they don't fill the parent.
*   **Touch Mode**: Ensures tabs are focusable and clickable.

### 2. Drawing
*   **Strips**: Draws `mLeftStrip` and `mRightStrip` images.
*   **Selection**: The strips align with the bounds of the selected child view.
*   **Divider**: Supports drawable dividers between tabs.

### 3. Interaction
*   **Focus**: `onFocusChange` logic (mostly handled by TabHost).
*   **Click**: Notifies `TabHost` via `OnTabSelectionChanged`.

## Java-to-C++ Translation Guide
*   **Decoration**: Custom drawing in `dispatchDraw` for the selection strip.
*   **Accessibility**: Exposes scroll/page actions if tabs overflow (though `TabWidget` itself usually doesn't scroll; `HorizontalScrollView` wrapping it would).

## Implementation Risks
*   **Legacy**: Heavily tied to the old 9-patch "tab" visual style of Android 2.x-4.x. Modern apps use `TabLayout`.
