# TraceReportParams - Reverse Engineering Documentation

## Executive Summary
Parcelable data holder for reporting a collected trace. Passed via `ITracingServiceProxy`.

## Data Model
*   **`reporterPackageName`**: Package name of the reporting service.
*   **`reporterClassName`**: Class name of the reporting service.
*   **`fd`**: `ParcelFileDescriptor` for the trace file (usually `O_TMPFILE`).
*   **`uuidLsb`, `uuidMsb`**: UUID of the trace.
*   **`usePipeForTesting`**: Boolean flag to force pipe-based transfer (for testing constraints).

## Java-to-C++ Translation Guide
*   **Struct**: Simple data structure/struct.
*   **IPC**: Used in Binder transactions.
