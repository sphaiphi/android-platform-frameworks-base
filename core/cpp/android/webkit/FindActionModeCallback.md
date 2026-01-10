# FindActionModeCallback - Reverse Engineering Documentation

## Executive Summary
`FindActionModeCallback` implements the UI logic for the "Find on Page" feature. It manages the `ActionMode` (the floating toolbar), the search text input, and communicates with the `WebView` to perform search operations.

## Architecture Overview
*   **Interfaces**: `ActionMode.Callback`, `TextWatcher`, `View.OnClickListener`, `WebView.FindListener`.
*   **UI Components**: Uses a custom view (`webview_find.xml`) containing an `EditText` and `TextView` (matches counter).

## Detailed Functionality
*   **Search Trigger**: `setText()` or user typing in the `EditText` triggers `findAll()`.
*   **Navigation**: "Next" and "Previous" buttons call `findNext(boolean)`.
*   **Feedback**: `onFindResultReceived` updates the "1 of X" match count.
*   **Soft Keyboard**: Manages showing/hiding the IME.

## Java-to-C++ Translation Guide
*   **UI Logic**: This is heavily Android View-dependent. In a pure C++ engine, this would be part of the "Chrome" (browser UI) layer, typically implemented in the native UI framework (e.g., Views on Linux/Windows, Cocoa on Windows). For Android C++ framework, this remains in Java/JNI.
*   **Interaction**: Calls `WebView::findAllAsync` and `WebView::findNext`.
