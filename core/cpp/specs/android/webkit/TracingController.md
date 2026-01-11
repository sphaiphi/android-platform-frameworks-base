# TracingController - Reverse Engineering Documentation

## Executive Summary
`TracingController` manages system-wide tracing for debugging and profiling WebViews.

## Detailed Functionality
*   **`start(TracingConfig)`**: Begins tracing.
*   **`stop(OutputStream, Executor)`**: Stops tracing and streams the data (JSON/Proto) to the provided output stream.
*   **`isTracing()`**: Check status.

## Java-to-C++ Translation Guide
*   **Perfetto Bridge**: Integration with the system tracing daemon (Perfetto) or internal Chrome tracing.
