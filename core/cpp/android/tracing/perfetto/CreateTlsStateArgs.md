# CreateTlsStateArgs - Reverse Engineering Documentation

## Executive Summary
Arguments wrapper passed when creating custom Thread Local Storage (TLS) state for a Perfetto data source. Similar to `CreateIncrementalStateArgs`, it provides access to the `DataSourceInstance`.

## Data Model
*   **`mDataSource`**: Reference to the `DataSource`.
*   **`mInstanceIndex`**: Index of the specific data source instance.

## API Reference
*   **`getDataSourceInstanceLocked()`**: Returns the `DataSourceInstance`.

## Java-to-C++ Translation Guide
*   **Helper Class**: Analogous to `CreateIncrementalStateArgs`, bridging Java context to the creation of TLS objects.
