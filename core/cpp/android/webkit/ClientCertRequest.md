# ClientCertRequest - Reverse Engineering Documentation

## Executive Summary
`ClientCertRequest` allows the application to handle SSL client certificate requests from the WebView. It provides details about the request (host, port, key types, principals) and methods to proceed, ignore, or cancel the request.

## Architecture Overview
*   **Role**: Callback object for `WebViewClient#onReceivedClientCertRequest`.
*   **Interaction**: User calls `proceed()`, `ignore()`, or `cancel()` on the UI thread.

## Detailed Functionality
*   **`proceed(PrivateKey, X509Certificate[])`**: Uses the provided key and chain for authentication.
*   **`ignore()`**: Ignores the request (doesn't save choice).
*   **`cancel()`**: Cancels the request (saves choice).
*   **Getters**: `getKeyTypes()`, `getPrincipals()`, `getHost()`, `getPort()`.

## Java-to-C++ Translation Guide
*   **Async Handling**: The C++ equivalent needs to handle the asynchronous nature of user certificate selection (which might involve system dialogs).
*   **Crypto Types**: Map `PrivateKey` and `X509Certificate` to the underlying SSL/TLS library's certificate and key structures (e.g., OpenSSL/BoringSSL objects).

## Implementation Risks
*   **Thread Safety**: Methods must be called on the UI thread.
