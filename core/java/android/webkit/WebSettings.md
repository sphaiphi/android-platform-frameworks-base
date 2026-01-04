# WebSettings - Reverse Engineering Documentation

## Executive Summary
`WebSettings` manages the configuration state for a `WebView`. It controls everything from JavaScript execution to zooming, fonts, and cache behavior.

## Detailed Functionality
*   **JavaScript**: `setJavaScriptEnabled`.
*   **Zoom**: `setSupportZoom`, `setBuiltInZoomControls`, `setDisplayZoomControls`, `setTextZoom`.
*   **Content Access**: `setAllowFileAccess`, `setAllowContentAccess`.
*   **Layout**: `setLayoutAlgorithm`, `setLoadWithOverviewMode`, `setUseWideViewPort`.
*   **Storage**: `setDomStorageEnabled`, `setDatabaseEnabled` (deprecated).
*   **User Agent**: `setUserAgentString`.
*   **Security**: `setMixedContentMode`, `setSafeBrowsingEnabled`.
*   **Dark Mode**: `setForceDark`, `setAlgorithmicDarkeningAllowed`.

## Java-to-C++ Translation Guide
*   **Preferences**: Maps to `WebPreferences` or `BrowserSettings` in the engine.
*   **Sync**: Changing settings often triggers IPC to the renderer process to update the active view.
