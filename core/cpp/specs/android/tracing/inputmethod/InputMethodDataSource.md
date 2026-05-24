# InputMethodDataSource - Reverse Engineering Documentation

## Executive Summary
`InputMethodDataSource` is a concrete implementation of the Perfetto `DataSource` class, specifically designed for tracing input method related events (likely IME tracing). It provides a mechanism to start and stop tracing with callbacks.

## Architecture Overview
*   **Inheritance**: Extends `DataSource<DataSourceInstance, Void, Void>`.
*   **Registration**: Identified by `DATA_SOURCE_NAME = "android.inputmethod"`.
*   **Callbacks**: Utilizes `Runnable` callbacks (`mOnStartCallback`, `mOnStopCallback`) to trigger logic in the input method system when tracing starts or stops.

## Data Model
*   **`mOnStartCallback`**: `Runnable` invoked when the data source is started.
*   **`mOnStopCallback`**: `Runnable` invoked when the data source is stopped.

## API Reference
*   **`InputMethodDataSource(Runnable onStart, Runnable onStop)`**: Constructor accepting start and stop callbacks.
*   **`createInstance(ProtoInputStream configStream, int instanceIndex)`**: Creates a new anonymous `DataSourceInstance`.
    *   The created instance overrides `onStart` and `onStop` to execute the runnables provided in the constructor.

## Java-to-C++ Translation Guide
*   **Perfetto SDK**: This wraps the Perfetto SDK's `DataSource`. In C++, this corresponds to defining a subclass of `perfetto::DataSource`.
*   **Callbacks**: The `Runnable` pattern maps to `std::function` or function pointers in C++.
