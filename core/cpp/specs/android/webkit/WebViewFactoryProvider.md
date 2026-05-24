# WebViewFactoryProvider - Reverse Engineering Documentation

## Executive Summary
`WebViewFactoryProvider` is the interface that the dynamically loaded WebView implementation must implement. It is the root of the backend implementation.

## Architecture Overview
*   **Entry Point**: `WebViewFactory` calls `create(WebViewDelegate)`.
*   **Sub-Providers**:
    *   `Statics`: Static methods (findAddress, etc.).
    *   `createWebView`: Creates the `WebViewProvider` delegate for a specific WebView instance.
    *   Getters for singletons: `getCookieManager`, `getWebStorage`, `getTracingController`, etc.

## Detailed Functionality
*   **Compatibility**: Includes version checks (`isCompatibleImplementationPackage`).
*   **Factory Methods**: `createWebView`, `getGeolocationPermissions`, `getServiceWorkerController`.

## Java-to-C++ Translation Guide
*   **Abstract Factory**: This is the Abstract Factory pattern separating the API (android.webkit) from the Implementation (com.android.webview.chromium).
