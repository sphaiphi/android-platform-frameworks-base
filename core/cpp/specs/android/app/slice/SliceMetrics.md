# SliceMetrics - Reverse Engineering Documentation

## Executive Summary
`SliceMetrics` provides a standardized way to log user interactions and visibility events for Slices. It wraps Android's internal `MetricsLogger`.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Dependencies**: `com.android.internal.logging.MetricsLogger`, `android.metrics.LogMaker`.

## Detailed Functionality

### Logging Lifecycle
1.  **Initialization**: Captures the Slice Uri.
2.  **Visible/Hidden**: Logs `TYPE_OPEN` and `TYPE_CLOSE` events.
3.  **Touch**: Logs `TYPE_ACTION` events with sub-slice information.

### Thread Safety
*   Uses `synchronized (mLogMaker)` for all operations, implying `LogMaker` is not thread-safe or the logger instance is shared.

## Data Model

### `LogMaker` Configuration
*   **Category**: `MetricsEvent.SLICE`
*   **Tagged Data**:
    *   `FIELD_SLICE_AUTHORITY`: Uri authority.
    *   `FIELD_SLICE_PATH`: Uri path.
    *   `FIELD_SUBSLICE_AUTHORITY`, `FIELD_SUBSLICE_PATH`: For touch events on sub-items.

## Java-to-C++ Translation Guide

### Metrics Subsystem
*   **Requirement**: A C++ equivalent of `MetricsLogger` (part of `liblog` or `statsd` client).
*   **Protocol**: If the Java `MetricsLogger` writes to `statsd`, the C++ implementation should write to the same atoms/events.

## Implementation Risks
*   **Dependencies**: `MetricsLogger` and `MetricsEvent` are internal Android classes. Reimplementing this requires access to the underlying logging transport (likely `statsd` socket).
