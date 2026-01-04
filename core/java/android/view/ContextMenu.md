# ContextMenu - Reverse Engineering Documentation

## Executive Summary
`ContextMenu` is an extension of the `Menu` interface specifically for menus that appear when a user long-presses a View. It adds functionality to manage a header (title, icon, or custom view) for the menu.

## Architecture Overview
*   **Interface**: Extends `Menu`.
*   **Lifecycle**: Views register for context menus via `Activity.registerForContextMenu()`. When a long-press is detected, the system calls `onCreateContextMenu()` on the view or its listeners.

## Detailed Functionality

### Header Management
*   **`setHeaderTitle()`**: Sets the text shown at the top of the context menu.
*   **`setHeaderIcon()`**: Sets an image for the header.
*   **`setHeaderView()`**: Replaces the standard title/icon header with a custom `View`.
*   **`clearHeader()`**: Removes any previously set header.

### Metadata
*   **`ContextMenuInfo`**: An interface for passing additional data about the item that triggered the menu (e.g., the position of an item in a list).

## Java-to-C++ Translation Guide
*   **Mapping**: In a C++ UI toolkit, this should be part of the menu system, likely implemented as a specialized `Menu` object with a `Header` property.

## Implementation Risks
*   **Legacy Support**: Context menus traditionally do not support item shortcuts or icons (unlike Options Menus), and C++ implementations should respect this limitation for consistency.
