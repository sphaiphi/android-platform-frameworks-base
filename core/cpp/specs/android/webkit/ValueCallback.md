# ValueCallback - Reverse Engineering Documentation

## Executive Summary
`ValueCallback<T>` is a generic callback interface for receiving values asynchronously. Used extensively in WebView APIs (e.g., `evaluateJavascript`, `saveWebArchive`).

## Detailed Functionality
*   **`onReceiveValue(T value)`**: The callback method.

## Java-to-C++ Translation Guide
*   **std::function**: Maps to `std::function<void(T)>` or a completion callback object.
