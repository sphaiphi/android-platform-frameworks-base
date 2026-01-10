# TransitionDataSource - Reverse Engineering Documentation

## Executive Summary
A concrete Perfetto `DataSource` for Window Manager / Shell transitions.

## Architecture Overview
*   **Inheritance**: Extends `DataSource<DataSourceInstance, Void, Void>`.
*   **Identity**: `DATA_SOURCE_NAME = "com.android.wm.shell.transition"`.
*   **Callbacks**: Uses `Runnable` callbacks for Start, Flush, and Stop events.

## API Reference
*   **`TransitionDataSource(Runnable onStart, Runnable onFlush, Runnable onStop)`**: Constructor.
*   **`createInstance`**: Creates an instance that invokes the static callbacks provided in the constructor.

## Java-to-C++ Translation Guide
*   **Pattern**: Identical to `InputMethodDataSource`. Wraps native Perfetto logic for a specific data source name.
