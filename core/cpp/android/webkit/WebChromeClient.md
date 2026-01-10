# WebChromeClient - Reverse Engineering Documentation

## Executive Summary
`WebChromeClient` handles JavaScript dialogs, favicons, titles, and the loading progress. It is distinct from `WebViewClient`, which handles content loading. It allows the host application to customize the browser chrome (UI around the web page).

## Detailed Functionality
*   **UI Events**:
    *   `onProgressChanged`: Loading progress (0-100).
    *   `onReceivedTitle`, `onReceivedIcon` (favicon), `onReceivedTouchIconUrl`.
*   **Custom Views (Fullscreen)**: `onShowCustomView`, `onHideCustomView`. Used for HTML5 video fullscreen.
*   **Multiple Windows**: `onCreateWindow`, `onCloseWindow`.
*   **Dialogs**: `onJsAlert`, `onJsConfirm`, `onJsPrompt`, `onJsBeforeUnload`.
*   **Permissions**: `onPermissionRequest`, `onGeolocationPermissionsShowPrompt`.
*   **Files**: `onShowFileChooser` (HTML input type=file).
*   **Console**: `onConsoleMessage`.

## Java-to-C++ Translation Guide
*   **Delegate**: This is the primary delegate for UI-related events from the engine.
*   **Fullscreen**: Requires integration with the windowing system to reparent views.
