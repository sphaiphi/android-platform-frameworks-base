# CreateIncrementalStateArgs - Reverse Engineering Documentation

## Executive Summary
Arguments wrapper passed when creating custom incremental state for a Perfetto data source. It allows safe retrieval of the `DataSourceInstance`.

## Data Model
*   **`mDataSource`**: Reference to the `DataSource`.
*   **`mInstanceIndex`**: Index of the specific data source instance.

## API Reference
*   **`getDataSourceInstanceLocked()`**: Returns the `DataSourceInstance` associated with this state. Requires calling `releaseDataSourceInstanceLocked` (implied by the `DataSource` API contract, though not enforced by this class directly) when done.

## Java-to-C++ Translation Guide
*   **Helper Class**: This is a helper for the Java-side Perfetto bridge. C++ Perfetto uses templates and direct access to state, so this exact wrapper might not have a direct 1:1 equivalent in user code, but maps to internal Perfetto SDK mechanics for state initialization.
