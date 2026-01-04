# WebViewFactory - Reverse Engineering Documentation

## Executive Summary
`WebViewFactory` is the static factory class responsible for loading the WebView implementation (provider) and creating instances of `WebViewFactoryProvider`. It manages the dynamic loading of the WebView APK.

## Architecture Overview
*   **Dynamic Loading**: Loads the WebView native library (`libwebviewchromium.so`) and Java classes from the WebView package (e.g., `com.google.android.webview`).
*   **Zygote**: Prepares address space in the Zygote process to ensure the library can load.
*   **Provider**: Caches the singleton `WebViewFactoryProvider`.

## Detailed Functionality
*   **`getProvider()`**: Main entry point. Returns the provider instance.
*   **`loadWebViewNativeLibraryFromPackage`**: Loads the native code.
*   **`getWebViewContextAndSetProvider`**: Creates the Context for the WebView APK.
*   **Timestamps**: Tracks startup performance (`StartupTimestamps`).

## Java-to-C++ Translation Guide
*   **Dynamic Loader**: This logic is specific to Android's updatable WebView architecture. A static build wouldn't need this complex loading logic.
