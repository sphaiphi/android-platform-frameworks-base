# CookieSyncManager - Reverse Engineering Documentation

## Executive Summary
`CookieSyncManager` is a deprecated class that was used to synchronize the in-memory cookie store with persistent storage. In modern versions, `CookieManager` handles this automatically, and `CookieManager#flush()` can be used for forced synchronization.

## Architecture Overview
*   **Status**: Deprecated.
*   **Inheritance**: Extends `WebSyncManager`.

## Detailed Functionality
*   **`sync()`**: Calls `CookieManager.getInstance().flush()`.
*   **Lifecycle**: `createInstance()`, `startSync()`, `stopSync()` are largely no-ops or delegate to automatic mechanisms.

## Java-to-C++ Translation Guide
*   **Obsolete**: This class is a wrapper for backward compatibility. In a new C++ implementation, rely on the `CookieManager` implementation's internal flushing mechanism.
