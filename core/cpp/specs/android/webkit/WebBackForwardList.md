# WebBackForwardList - Reverse Engineering Documentation

## Executive Summary
`WebBackForwardList` represents the navigation history of a `WebView`.

## Detailed Functionality
*   **`getCurrentItem()`**: Returns the `WebHistoryItem` for the current page.
*   **`getCurrentIndex()`**: Index of the current item.
*   **`getItemAtIndex(index)`**: Access specific items.
*   **`getSize()`**: Total list size.

## Java-to-C++ Translation Guide
*   **Navigation Controller**: Maps to the browser's `NavigationController` or `HistoryService`.
