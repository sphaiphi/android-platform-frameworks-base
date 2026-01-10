# IncrementalMetrics - Reverse Engineering Documentation

## Executive Summary
`IncrementalMetrics` is a read-only wrapper around a `PersistableBundle` containing metrics retrieved from the Incremental Service. It provides typed getters for specific metric keys related to read delays, errors, and loader status.

## Architecture Overview
-   **Pattern**: Data Accessor / Wrapper.
-   **Source**: `PersistableBundle` returned by `IIncrementalService.getMetrics()`.

## Data Model
-   **Keys**: Constants defined in `IIncrementalService` (e.g., `METRICS_TOTAL_DELAYED_READS`).

## API Reference
-   `getMillisSinceOldestPendingRead()`
-   `getReadLogsEnabled()`
-   `getStorageHealthStatusCode()`
-   `getDataLoaderStatusCode()`
-   `getTotalDelayedReads()`
-   `getTotalFailedReads()`
-   `getLastReadErrorUid()`
-   ...and others.

## Java-to-C++ Translation Guide
-   **Keys**: Access the string constants in `IIncrementalService.aidl`.
-   **Data Structure**: In C++, this would likely be a `struct` populated from the Binder return value (which might be a `PersistableBundle` equivalent or a custom Parcelable).