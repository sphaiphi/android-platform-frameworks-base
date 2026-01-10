# WebViewZygote - Reverse Engineering Documentation

## Executive Summary
`WebViewZygote` manages a specialized Zygote process for spawning WebView renderer processes. This isolates the WebView code from the rest of the system and allows for sharing RELRO memory.

## Architecture Overview
*   **Child Zygote**: Starts `com.android.internal.os.WebViewZygoteInit`.
*   **Isolation**: Runs with `WEBVIEW_ZYGOTE_UID`.

## Detailed Functionality
*   **`getProcess()`**: Returns the Zygote connection.
*   **`onWebViewProviderChanged()`**: Restarts the Zygote when the WebView package updates (to load the new code).

## Java-to-C++ Translation Guide
*   **Process Management**: This is a core Android OS feature (Zygote).
