# HttpAuthHandler - Reverse Engineering Documentation

## Executive Summary
`HttpAuthHandler` handles HTTP authentication requests (Basic/Digest). It acts as a bridge between the network stack's auth challenge and the application's response (providing credentials or cancelling).

## Detailed Functionality
*   **`proceed(username, password)`**: Submits credentials.
*   **`cancel()`**: Aborts the auth request.
*   **`useHttpAuthUsernamePassword()`**: Checks if saved credentials should be used (legacy).

## Java-to-C++ Translation Guide
*   **Handler Pattern**: This is effectively a callback object. In C++, this would be a `LoginDelegate` or `AuthCallback`.
*   **Thread Safety**: Explicitly documented to require UI thread usage for callbacks.
