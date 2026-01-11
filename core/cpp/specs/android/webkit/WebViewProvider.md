# WebViewProvider - Reverse Engineering Documentation

## Executive Summary
`WebViewProvider` is the interface that delegates *every* method of the `WebView` class. For every method in `WebView`, there is a corresponding method here.

## Architecture Overview
*   **Delegation**: `WebView` calls `mProvider.method()`.
*   **ViewDelegate**: Interface for delegating `View` and `ViewGroup` methods (e.g., `onDraw`, `onTouchEvent`).
*   **ScrollDelegate**: Interface for scrolling methods.

## Detailed Functionality
*   **Lifecycle**: `init()`, `destroy()`.
*   **Functionality**: `loadUrl`, `evaluateJavaScript`, `goBack`, etc.

## Java-to-C++ Translation Guide
*   **Implementation Base**: The C++ backing class (e.g., `AwContents` in Chromium) implements the logic behind these methods.
