# MenuPopupWindow - Reverse Engineering Documentation

## Executive Summary
`MenuPopupWindow` is a specialized `ListPopupWindow` used for displaying menus. It adds behavior for hover listeners (to support submenus) and transition animations.

## Architecture Overview
*   **Inheritance**: `ListPopupWindow` -> `MenuPopupWindow`.
*   **Internal Class**: `MenuDropDownListView`.

## Detailed Functionality
*   **Hover**: Sets a `MenuItemHoverListener` on the internal list view.
*   **Transitions**: Supports enter/exit transitions.
*   **`MenuDropDownListView`**: Overrides `onKeyDown` to handle left/right arrow keys for navigating into/out of submenus.

## Java-to-C++ Translation Guide
*   **Input Handling**: The key forwarding logic for submenus is the primary addition.

## Implementation Risks
*   **Timing**: Hover logic often needs delays to prevent flickering submenus.
