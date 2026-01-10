# WebViewClient - Reverse Engineering Documentation

## Executive Summary
`WebViewClient` is the primary interface for handling content-related events during the `WebView` lifecycle. It allows the app to intercept requests, handle errors, and manage navigation.

## Detailed Functionality
*   **Navigation Interception**:
    *   **`shouldOverrideUrlLoading(view, request)`**: Decides if the WebView should load the URL or if the app wants to handle it (e.g., launch an Intent).
*   **Lifecycle**:
    *   `onPageStarted()`: Load begins.
    *   `onPageFinished()`: Load ends (critical for injecting JS).
    *   `onPageCommitVisible()`: Content is visually committed.
*   **Resource Interception**:
    *   **`shouldInterceptRequest(view, request)`**: Allows the app to provide the response body for a request (e.g., loading local assets instead of network).
*   **Errors**:
    *   `onReceivedError()`: Network/loading errors.
    *   `onReceivedHttpError()`: HTTP status errors (4xx/5xx).
    *   `onReceivedSslError()`: SSL validation failures.
    *   `onSafeBrowsingHit()`: Malware/Phishing detection.
    *   `onRenderProcessGone()`: Renderer crash handling.
*   **Other**:
    *   `onScaleChanged()`: Zoom changes.
    *   `doUpdateVisitedHistory()`: History updates.
    *   `onReceivedLoginRequest()`: Auto-login.

## Java-to-C++ Translation Guide
*   **Navigation Delegate**: Maps to `WebContentsDelegate` or `NavigationDelegate` in Chromium.
*   **Resource Interceptor**: Maps to the network stack's interception layer.
