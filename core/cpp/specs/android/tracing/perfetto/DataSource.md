# DataSource - Reverse Engineering Documentation

## Executive Summary
`DataSource` is the abstract base class for creating custom Perfetto data sources in Java. It wraps a native C++ Perfetto data source object and manages the lifecycle of tracing sessions, instances, and trace packet writing.

## Architecture Overview
*   **Native Bridge**: Holds a `mNativeObj` pointer to a C++ object that bridges to the native Perfetto SDK.
*   **Generics**: Templated on `DataSourceInstanceType`, `TlsStateType`, and `IncrementalStateType` to support custom per-instance and per-thread state.
*   **Tracing Loop**: Implements the efficient tracing loop pattern (`trace()`) calling into native code to acquire buffers and context.

## API Reference
*   **`createInstance(ProtoInputStream, int)`**: Abstract method. Implementers must return a new `DataSourceInstance`.
*   **`trace(TraceFunction fun)`**: The primary API for writing trace data.
    *   Iterates over active instances.
    *   Creates a `TracingContext`.
    *   Executes the provided lambda/function.
    *   Writes packets from the context to native.
*   **`flush()`**: Flushes pending data.
*   **`createTlsState(...)`**: Factory method for custom thread-local state.
*   **`createIncrementalState(...)`**: Factory method for custom incremental state.
*   **`register(DataSourceParams)`**: Registers the data source with the Perfetto backend.
*   **`getDataSourceInstanceLocked(int)`**: Retrieves a specific instance (thread-safe lock on native side).
*   **`releaseDataSourceInstance(int)`**: Releases the lock.

## Java-to-C++ Translation Guide
*   **Core Logic**: This *is* the wrapper around the C++ `perfetto::DataSource`.
*   **Native Methods**: The private native methods (`nativeCreate`, `nativeTraceIterate...`, etc.) map directly to calls into the Perfetto C++ SDK (specifically the `DataSource` template).
