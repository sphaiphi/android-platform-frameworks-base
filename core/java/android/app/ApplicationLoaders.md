# ApplicationLoaders - Reverse Engineering Documentation

## Executive Summary
`ApplicationLoaders` is a singleton responsible for creating and caching `ClassLoader` instances for applications and shared libraries. It ensures that class loaders for the same path are reused and properly configured (e.g., with native library paths).

## Architecture Overview
*   **Pattern**: Singleton.
*   **Key Data**: `mLoaders` (ArrayMap<String, ClassLoader>), `mSystemLibsCacheMap`.
*   **Dependencies**: `ClassLoaderFactory`, `GraphicsEnvironment`.

## Detailed Functionality

### ClassLoader Creation
*   `getClassLoader(...)`: Main entry point.
*   **Caching**: Checks `mLoaders` using the zip path as key. Returns cached loader if found.
*   **Creation**: If not cached, calls `ClassLoaderFactory.createClassLoader`.
*   **Configuration**: Sets layer paths in `GraphicsEnvironment`.

### Shared Library Support
*   `getSharedLibraryClassLoaderWithSharedLibraries`: Handles loading of shared libs with dependencies.
*   `createAndCacheNonBootclasspathSystemClassLoaders`: Pre-caches system libs (zygote optimization).

### WebView Support
*   `createAndCacheWebViewClassLoader`: Specialized method for WebView's APK.

## Java-to-C++ Translation Guide
*   **JVM Specific**: This class manages Java ClassLoaders. In a pure C++ environment (if no JVM), this is irrelevant.
*   **If implementing Android Runtime**: This is a critical component for managing the classpath and native library paths (`java.library.path`) for ART.

## Implementation Risks
*   **Concurrency**: Access to `mLoaders` must be synchronized.
*   **Circular Dependencies**: Shared library dependencies must be handled carefully.
