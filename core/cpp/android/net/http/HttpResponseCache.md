# HttpResponseCache.java - Reverse Engineering Documentation

## Executive Summary
`HttpResponseCache` is an implementation of `java.net.ResponseCache` that provides file-based caching for HTTP and HTTPS responses. It wraps an `AndroidResponseCacheAdapter` which likely bridges to the OkHttp caching mechanism (given the imports `com.android.okhttp...`).

## Architecture Overview
- **Type**: Cache Implementation
- **Package**: `android.net.http`
- **Extends**: `java.net.ResponseCache`
- **Implements**: `Closeable`
- **Dependency**: `com.android.okhttp.internalandroidapi.AndroidResponseCacheAdapter` (Internal API).

## Detailed Functionality

### Installation (`install`)
-   **Static Method**: `install(File directory, long maxSize)`.
-   **Logic**:
    1.  Checks if a cache is already installed. If it's an `HttpResponseCache` with the same directory and size, it returns the existing instance.
    2.  If different, it closes the existing one.
    3.  Creates a new `CacheHolder` (internal OkHttp wrapper) and `AndroidResponseCacheAdapter`.
    4.  Sets the new cache as the system default via `ResponseCache.setDefault()`.

### Core Operations
-   **`get`**: Retrieves cached response. Delegates to adapter.
-   **`put`**: Caches a request/response pair. Delegates to adapter.
-   **`size`/`maxSize`**: Statistics.
-   **`flush`**: Persists data to filesystem.
-   **`close`/`delete`**: Lifecycle management.

### Statistics
-   `getNetworkCount()`: Requests that required network.
-   `getHitCount()`: Requests served from cache.
-   `getRequestCount()`: Total requests.

## Java-to-C++ Translation Guide
-   This class relies heavily on Java's `java.net` networking stack and the Android-specific OkHttp integration.
-   In a C++ environment, you would typically use a library like `libcurl` or `Cronet` (which has its own disk cache implementation) rather than porting this directly.
-   If implementing from scratch:
    -   Need a disk LRU cache implementation.
    -   Need to intercept HTTP requests/responses (Middleware pattern).
    -   Adhere to HTTP caching RFCs (Cache-Control headers, etc.).
