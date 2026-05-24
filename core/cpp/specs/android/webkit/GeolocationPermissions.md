# GeolocationPermissions - Reverse Engineering Documentation

## Executive Summary
`GeolocationPermissions` manages permissions for the Geolocation API in `WebView`. It allows listing, allowing, clearing, and denying access for specific web origins.

## Architecture Overview
*   **Singleton**: Accessed via `getInstance()`.
*   **Callback**: `Callback` interface for async responses.
*   **Origins**: Represented as Strings (scheme://host:port).

## Detailed Functionality
*   **`getOrigins(Callback)`**: Asynchronously retrieves all origins with stored permissions.
*   **`getAllowed(origin, Callback)`**: Checks permission for a specific origin.
*   **`allow(origin)`**: Grants permission.
*   **`clear(origin)`**: Removes permission.
*   **`clearAll()`**: Clears all permissions.

## Java-to-C++ Translation Guide
*   **Permission Store**: Maps to the browser engine's permission context (e.g., `GeolocationPermissionContext` in Chromium).
*   **Async**: All read operations are async; write operations (allow/clear) might be fire-and-forget or async depending on the backend.
