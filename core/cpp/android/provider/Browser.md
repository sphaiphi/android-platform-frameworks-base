# Browser - Reverse Engineering Documentation

## Executive Summary
`Browser` contains legacy utilities and constants for interacting with the (deprecated) system browser provider (`BrowserProvider`). It includes intents for adding bookmarks, viewing searches, and accessing history.

**Note**: Most of this is deprecated or removed.

## Architecture Overview
- **Type**: Utility Class.
- **Legacy**: Targets the old `com.android.browser` authority.

## Detailed Functionality
-   **Intents**: `saveBookmark`, `sendString`.
-   **Cursors**: `getAllBookmarks`, `getAllVisitedUrls`.
-   **History Management**: `clearHistory`, `deleteFromHistory`, `truncateHistory`.
-   **Tables**: `BookmarkColumns`, `SearchColumns`.

## Data Model
-   **Columns**: `url`, `visits`, `date`, `bookmark`, `title`, `favicon`, `thumbnail`.

## Java-to-C++ Translation Guide
-   **Deprecation**: Verify if the target platform still supports `com.android.browser`. Likely obsolete for modern Android.
