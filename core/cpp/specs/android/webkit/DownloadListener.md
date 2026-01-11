# DownloadListener - Reverse Engineering Documentation

## Executive Summary
`DownloadListener` is an interface that allows the application to handle file downloads that the `WebView` cannot render itself.

## API Reference
*   **`onDownloadStart(url, userAgent, contentDisposition, mimetype, contentLength)`**:
    *   Called when a download should start.
    *   Provides all necessary metadata to hand off the download to the `DownloadManager` or handle it manually.

## Java-to-C++ Translation Guide
*   **Callback**: Define as a C++ interface/callback function (e.g., `std::function` or virtual class).
*   **Content-Disposition**: The C++ side needs to parse the HTTP headers to extract this information before calling the listener.
