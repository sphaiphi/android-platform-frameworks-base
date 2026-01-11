# BrowserContract - Reverse Engineering Documentation

## Executive Summary
`BrowserContract` defines the contract for the `com.android.browser` provider, supporting bookmarks, history, images, and sync state.

**Note**: Generally tied to the legacy AOSP Browser or Chrome's provider implementation.

## Architecture Overview
- **Type**: Contract Class.
- **Authority**: `com.android.browser`.
- **Inner Classes**: `Bookmarks`, `History`, `Searches`, `Images`, `SyncState`.

## Detailed Functionality
-   **Bookmarks**: Hierarchical folder structure (`IS_FOLDER`, `PARENT`). Supports sync columns.
-   **History**: Browsing history (`DATE_LAST_VISITED`, `VISITS`).
-   **Images**: Favicons and thumbnails (`DATA`, `URL`).
-   **Combined**: View joining bookmarks and history.

## Data Model
-   **Columns**: Standard content provider schema.

## Java-to-C++ Translation Guide
-   **URIs**: `content://com.android.browser/bookmarks`, etc.
-   **Columns**: Map string constants.
