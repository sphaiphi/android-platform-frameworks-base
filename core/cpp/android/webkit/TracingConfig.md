# TracingConfig - Reverse Engineering Documentation

## Executive Summary
`TracingConfig` defines the configuration for the `TracingController`. It specifies which categories to trace (e.g., rendering, JS, network) and the tracing mode (continuous ring buffer vs. until full).

## Data Model
*   **Categories**: Predefined masks (`CATEGORIES_WEB_DEVELOPER`, `CATEGORIES_RENDERING`) and custom strings.
*   **Mode**: `RECORD_CONTINUOUSLY` or `RECORD_UNTIL_FULL`.

## Java-to-C++ Translation Guide
*   **Trace Config**: Maps directly to the underlying tracing system configuration (e.g., Perfetto/Chrome Tracing config).
