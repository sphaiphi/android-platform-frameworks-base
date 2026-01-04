# DataSourceParams - Reverse Engineering Documentation

## Executive Summary
Configuration parameters for registering a data source.

## Data Model
*   **`bufferExhaustedPolicy`**: `DROP` (default) or `STALL_AND_ABORT`.
*   **`willNotifyOnStop`**: Whether the data source acknowledges stop requests (default: true).
*   **`noFlush`**: Whether the service should skip flush requests for this source (default: false).

## API Reference
*   **`Builder`**: Fluent builder for creating `DataSourceParams`.

## Java-to-C++ Translation Guide
*   **Perfetto Struct**: Maps to `perfetto::DataSourceDescriptor` fields or registration arguments in the C++ SDK.
