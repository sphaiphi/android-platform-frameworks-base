# CookieManager - Reverse Engineering Documentation

## Executive Summary
`CookieManager` is a singleton abstract class responsible for managing cookies used by `WebView` instances. It handles accepting cookies, third-party cookies, and setting/retrieving cookies for specific URLs. It implements the cookie jar for the browser engine.

## Architecture Overview
*   **Singleton**: Accessed via `getInstance()`.
*   **Scope**: Application-wide (process-wide), though some settings (third-party cookies) are per-WebView.
*   **Thread Safety**: Most methods are thread-safe or handle synchronization internally, but some callbacks run on specific threads.

## Detailed Functionality
*   **Acceptance**: `setAcceptCookie(boolean)`, `setAcceptThirdPartyCookies(WebView, boolean)`.
*   **Operations**:
    *   `setCookie(url, value)`: Sets a cookie (can be async with callback).
    *   `getCookie(url)`: Gets cookies for a URL as a string.
    *   `removeAllCookies()`, `removeSessionCookies()`: Clearing methods.
    *   `flush()`: Forces writing cookies to persistent storage.
*   **File Scheme**: `setAcceptFileSchemeCookies()` (Deprecated/Insecure).

## Java-to-C++ Translation Guide
*   **Cookie Jar**: Maps directly to the browser engine's cookie storage mechanism (e.g., `net::CookieStore` in Chromium).
*   **Async Operations**: `setCookie` and remove methods use callbacks; the C++ implementation must support async notification upon completion.
*   **Persistence**: `flush()` maps to triggering a write to the backing store (SQLite/JSON).

## Implementation Risks
*   **Synchronization**: Accessing cookies from multiple threads (UI vs Network) requires careful locking.
*   **Privacy**: Third-party cookie blocking logic must be correctly implemented to respect the setting.
