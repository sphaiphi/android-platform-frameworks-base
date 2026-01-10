# SslErrorHandler - Reverse Engineering Documentation

## Executive Summary
`SslErrorHandler` is passed to `onReceivedSslError`. It allows the app to `proceed()` (ignore certificate error) or `cancel()` (abort connection).

## Detailed Functionality
*   **`proceed()`**: Ignore error.
*   **`cancel()`**: Abort.

## Java-to-C++ Translation Guide
*   **SSL Manager**: Interactions with `SslErrorHandler` usually update the `SSLPolicy` or `CertVerifier` state for the request.
