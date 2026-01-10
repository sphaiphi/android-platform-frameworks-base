# PropertyInvalidatedCache - Reverse Engineering Documentation

## Executive Summary
`PropertyInvalidatedCache` is an optimized LRU cache designed for cross-process data caching. It uses a "nonce" (a unique value) stored in a system property or shared memory to determine if the cached data is still valid. When the server modifies data, it increments the nonce, signaling all clients to invalidate their local caches. This mechanism provides low-latency access to expensive Binder calls while ensuring data consistency. It is the underlying engine for `IpcDataCache`.

## Architecture Overview
- **Core Components**:
    - `mCache`: A `CacheMap` (inner class) that stores results keyed by a `Query`. It optionally isolates entries by the calling UID.
    - `mNonce`: A `NonceHandler` (inner class) that abstracts the storage of the invalidation token.
    - `QueryHandler`: A user-provided function that computes the result on a cache miss (`recompute`).
- **Nonce Handlers**:
    - `NonceSysprop`: Stores nonces in standard system properties.
    - `NonceSharedMem`: Stores nonces in a specialized shared memory block (`NonceStore`) for even lower overhead.
    - `NonceLocal`: Stores nonces in process memory (used for tests).
- **Management**: Tracks hits, misses, and "skips" (requests that bypassed the cache).

## Detailed Functionality

### Query Logic (`query(Query query)`)
**Purpose**: Retrieves a value from the cache or recomputes it.
**Algorithm**:
1. Checks if caching is enabled or if the query should bypass the cache.
2. Fetches the current nonce from the `mNonce` handler.
3. If the nonce matches the `mLastSeenNonce`, it checks the LRU map for a hit.
4. If the nonce has changed, it clears the cache and updates `mLastSeenNonce`.
5. On a hit, it calls `refresh()` to allow the user to augment the data.
6. On a miss, it calls `recompute()` via the `QueryHandler`, stores the result in the map, and returns it.

### Invalidation (`invalidateCache(...)`)
**Purpose**: Signals that the source data has changed.
**Mechanism**: Increments the nonce in the configured storage (system property or shared memory). This is a synchronous operation that affects all processes using the same cache key.

### Corking (`corkInvalidations` / `uncorkInvalidations`)
**Purpose**: Amortizes the cost of frequent invalidations (e.g., bulk updates).
**Logic**: While a cache is "corked", invalidation requests are suppressed, and clients are forced to bypass the cache and talk to the server directly. This ensures they always see the most recent data during a multi-step update process.

### Shared Memory Optimization (`NonceStore`)
**Purpose**: Provides ultra-fast nonce lookups.
**Algorithm**: 
- Uses a `NonceStore` singleton mapped to a native shared memory block.
- Nonce names are mapped to indices in a native array.
- Lookups use `CriticalNative` JNI methods for near-zero overhead.

## API Reference
- `public Result query(Query query)`: Main entry point.
- `public void invalidateCache()`: Triggers invalidation.
- `public void corkInvalidations()`: Starts a bulk update phase.
- `public void clear()`: Manually flushes the cache.
- `public static void setTestMode(boolean mode)`: Enables local-only behavior for unit tests.

## Java-to-C++ Translation Guide
- **LRU Map**: Map `CacheMap` to a `std::list` + `std::unordered_map` or a custom LRU implementation.
- **Shared Memory**: Use `ashmem` or `memfd_create` to implement the `NonceStore` in C++. Map the memory block using `mmap`.
- **System Properties**: Use `__system_property_find` and `__system_property_read_callback` for the `NonceSysprop` equivalent.
- **Atomic Nonces**: Use `std::atomic<int64_t>` for the nonce values in shared memory.

## Implementation Risks
- **Deadlocks**: The class uses nested locks (`mLock`, `sGlobalLock`, `sCorkLock`). C++ implementation must strictly adhere to the locking hierarchy to avoid deadlocks across multiple cache instances.
- **Race Conditions**: There is a potential race between `invalidate` and `disable`. The system property implementation is not atomic for compare-and-exchange operations.
- **Memory Pressure**: The cache must be able to react to memory pressure signals and flush its contents.
