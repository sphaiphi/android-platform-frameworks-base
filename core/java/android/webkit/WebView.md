# WebView - Reverse Engineering Documentation

## Executive Summary
`WebView` is the core UI component for displaying web pages in Android. It extends `AbsoluteLayout` (historically) but delegates all implementation details to a `WebViewProvider`. It is the primary entry point for embedding web content.

## Architecture Overview
*   **View**: Extends `AbsoluteLayout` (legacy) but acts as a standard View.
*   **Delegation**: Uses the **Bridge Pattern**. All public methods delegate to `mProvider` (an instance of `WebViewProvider`).
*   **Factory**: Created via `WebViewFactory`.
*   **Threading**: Must be created and used on a thread with a `Looper` (usually the UI thread). Enforces thread safety.

## Detailed Functionality

### 1. Loading Content
*   **`loadUrl(String)`**: Loads a web page.
*   **`loadData(data, mime, encoding)`**: Loads raw HTML.
*   **`loadDataWithBaseURL()`**: Loads raw HTML with a specific base URL (crucial for relative links and security).
*   **`postUrl()`**: Performs a POST request.
*   **`reload()`, `stopLoading()`**: Navigation control.

### 2. Navigation
*   **`goBack()`, `goForward()`**: History navigation.
*   **`canGoBack()`, `canGoForward()`**: Check availability.
*   **`copyBackForwardList()`**: Inspect history.

### 3. Integration & Configuration
*   **`setWebViewClient()`**: Handles navigation events, errors, and interception.
*   **`setWebChromeClient()`**: Handles UI events (titles, dialogs, favicons).
*   **`getSettings()`**: Returns `WebSettings` for configuration.
*   **`addJavascriptInterface()`**: Injects Java objects into the JS context.

### 4. Advanced Features
*   **`evaluateJavascript()`**: Async JS execution.
*   **`saveWebArchive()`**: Saves page as MHTML.
*   **`print()`**: Creates a `PrintDocumentAdapter`.
*   **`capturePicture()`**: (Deprecated) Captures content.

### 5. Process Management
*   **`getWebViewRenderProcess()`**: Access to the renderer handle (for multi-process termination).
*   **`setWebViewRenderProcessClient()`**: Listen for renderer crashes/unresponsiveness.

## Java-to-C++ Translation Guide
*   **Proxy Pattern**: The Java `WebView` is essentially a proxy. The C++ implementation (usually via JNI in `WebViewChromium`) handles the heavy lifting (Blink/V8).
*   **View Hierarchy**: `WebView` attaches to the Android View hierarchy. The native side usually provides a `SurfaceView` or `TextureView` (or draws directly to the `Canvas` via functors) to render web content.
*   **Input**: Touch and key events are forwarded to the native engine.

## Implementation Risks
*   **Thread Safety**: Strictly enforced. Accessing `WebView` from a background thread crashes the app (or throws exception).
*   **Memory**: WebViews are heavy. Loading many or keeping them around can cause OOM.
*   **Security**: `addJavascriptInterface` + untrusted content is a major vulnerability vector. `setAllowFileAccess(true)` is also risky.
