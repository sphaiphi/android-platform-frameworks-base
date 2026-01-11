# DataSourceInstance - Reverse Engineering Documentation

## Executive Summary
`DataSourceInstance` represents a live instance of a data source within a tracing session. It manages lifecycle callbacks (`onStart`, `onStop`, `onFlush`).

## API Reference
*   **`onStart(StartCallbackArguments)`**: Callback when tracing starts.
*   **`onFlush(FlushCallbackArguments)`**: Callback when a flush is requested.
*   **`onStop(StopCallbackArguments)`**: Callback when tracing stops.
*   **`release()`**: Unlocks the instance (if manually locked via `DataSource`).
*   **`close()`**: Alias for `release` (AutoCloseable).

## Java-to-C++ Translation Guide
*   **Perfetto Concept**: Maps to `perfetto::DataSource::Instance`. The lifecycle methods mirror the C++ virtual methods `OnStart`, `OnStop`, etc.
