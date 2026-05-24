# WebResourceRequest - Reverse Engineering Documentation

## Executive Summary
`WebResourceRequest` encapsulates details of a resource request intercepted by `WebViewClient`.

## Detailed Functionality
*   **`getUrl()`**: The target URI.
*   **`isForMainFrame()`**: True if this is the top-level navigation.
*   **`isRedirect()`**: True if part of a redirect chain.
*   **`hasGesture()`**: True if initiated by a user gesture.
*   **`getMethod()`**: HTTP method (GET, POST, etc.).
*   **`getRequestHeaders()`**: Map of headers.

## Java-to-C++ Translation Guide
*   **URLRequest**: Maps to the internal URL request object in the network stack.
