# ChangeIdStateCache - Reverse Engineering Documentation

## Executive Summary
`ChangeIdStateCache` is a specialized caching mechanism designed to reduce the overhead of cross-process calls (IPC) to the `platform_compat` system service. It specifically caches the "enabled" state of compatibility changes (feature flags/gates) for applications. It extends Android's `PropertyInvalidatedCache`, leveraging system properties to efficiently invalidate the cache when the underlying configuration changes.

## Architecture Overview
*   **Inheritance**: Extends `PropertyInvalidatedCache<ChangeIdStateQuery, Boolean>`.
*   **Component Type**: Client-side cache wrapper.
*   **Key Dependency**: `IPlatformCompat` (Binder interface to the System Server).
*   **Key Key-Value**:
    *   **Key**: `ChangeIdStateQuery` (Composite key: Change ID + Package Name/UID + User ID).
    *   **Value**: `Boolean` (Enabled/Disabled state).

## Detailed Functionality

### `recompute(ChangeIdStateQuery query)`
**Purpose**: Performs the actual lookup when a cache miss occurs. It contacts the `platform_compat` service via Binder IPC.
**Algorithm**:
1.  Clear the caller's identity (Binder identity) to ensure the call to the system service is treated as coming from this process but without carrying over the original caller's permissions context if it was an incoming IPC.
2.  Determine the query type from the `query` object:
    *   **QUERY_BY_PACKAGE_NAME**: Call `IPlatformCompat.isChangeEnabledByPackageName`.
    *   **QUERY_BY_UID**: Call `IPlatformCompat.isChangeEnabledByUid`.
3.  Handle `RemoteException` (IPC failure) by rethrowing it as a runtime exception.
4.  Restore the caller's identity.
5.  Return the result (`true`/`false`).

### `getPlatformCompatService()`
**Purpose**: Lazily initializes and returns the proxy to the `platform_compat` service.
**Algorithm**:
1.  Check if `mPlatformCompat` is already set.
2.  If not, enter a `synchronized` block (double-checked locking pattern).
3.  Retrieve the binder service `Context.PLATFORM_COMPAT_SERVICE` from `ServiceManager`.
4.  Convert it to the `IPlatformCompat` interface using `Stub.asInterface`.
5.  Cache and return the interface.

## Data Model

### Cache Configuration
*   **Module**: `MODULE_SYSTEM`
*   **API Name**: `is_compat_change_enabled` (Used for invalidation property naming).
*   **Max Entries**: 2048.
*   **Behavior**:
    *   `isolateUids(false)`: Cache is shared across UIDs if applicable (though logic usually queries specific UIDs).
    *   `cacheNulls(false)`: Null results are not cached.

## API Reference

### Public Static Methods (Internal Use)
*   `void disable()`: Disables the cache (mostly for testing).
*   `void invalidate()`: Invalidates the cache. Can only be called by the system server process.

### Protected Methods
*   `Boolean recompute(ChangeIdStateQuery query)`: Implementation of the abstract method from `PropertyInvalidatedCache`.

## Java-to-C++ Translation Guide

### Thread Safety & Singleton
*   **Java**: Uses `synchronized(this)` and `volatile` for lazy initialization.
*   **C++**: Use `std::mutex` and `std::atomic` or `std::call_once` for thread-safe lazy initialization of the service proxy.

### IPC / Binder
*   **Java**: `ServiceManager.getService(...)`, `IPlatformCompat.Stub.asInterface(...)`.
*   **C++**: Use `android::defaultServiceManager()->getService(...)` and cast to the generated AIDL interface `IPlatformCompat`.
    *   *Note*: Ensure the AIDL for `IPlatformCompat` is compiled for C++.

### Caching Strategy
*   **Java**: `PropertyInvalidatedCache`.
*   **C++**: Android's C++ libraries may have a native equivalent of `PropertyInvalidatedCache`. If not, implement a `std::map` or `std::unordered_map` protected by a `std::shared_mutex` (read/write lock).
    *   **Key**: A struct equivalent to `ChangeIdStateQuery`.
    *   **Value**: `bool`.
    *   **Invalidation**: Listen to the system property (e.g., via `__system_property_wait` or generic property change listeners) matching `cache_key.is_compat_change_enabled`.

### Identity Management
*   **Java**: `Binder.clearCallingIdentity()`, `Binder.restoreCallingIdentity(token)`.
*   **C++**: `IPCThreadState::self()->clearCallingIdentity()`, `IPCThreadState::self()->restoreCallingIdentity(token)`.

## Test Cases & Validation
1.  **Cache Miss**: Request a change ID that hasn't been queried. Verify `recompute` calls the Binder service.
2.  **Cache Hit**: Request the same ID again. Verify no Binder call is made.
3.  **Invalidation**: Trigger `invalidate()`. Verify the next request calls the Binder service.
4.  **Service Retrieval**: Verify `getPlatformCompatService` correctly connects to `platform_compat`.

## Implementation Risks
*   **Property Invalidation**: Ensure the C++ implementation correctly observes the system property change for invalidation. If this mechanism is missed, the cache will become stale.
*   **Concurrency**: The cache must be thread-safe as it will likely be accessed by multiple threads in a process.

## Questions for C++ Team
*   Is there a direct C++ port of `PropertyInvalidatedCache` available in `libbinder` or `libutils`?
*   Are the `IPlatformCompat` AIDL headers already available in the build target?
