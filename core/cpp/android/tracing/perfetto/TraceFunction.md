# TraceFunction - Reverse Engineering Documentation

## Executive Summary
Functional interface for the lambda passed to `DataSource.trace()`.

## API Reference
*   **`trace(TracingContext ctx)`**: The method implemented by user code to write trace events using the provided context.

## Java-to-C++ Translation Guide
*   **Lambda**: In C++, this is the lambda passed to `DataSource::Trace([](DataSource::TraceContext ctx) { ... })`.
