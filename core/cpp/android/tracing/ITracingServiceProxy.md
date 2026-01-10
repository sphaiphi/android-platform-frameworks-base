# ITracingServiceProxy - Reverse Engineering Documentation

## Executive Summary
`ITracingServiceProxy` is a Binder interface definition (`.aidl`) for the `TracingServiceProxy` running in `system_server`. It acts as a bridge for reporting trace events and session lifecycle updates to system tracing applications or services.

## API Reference
*   **`notifyTraceSessionEnded(boolean sessionStolen)`**:
    *   **Purpose**: Notifies the system tracing app that a tracing session has concluded.
    *   **Arguments**:
        *   `sessionStolen`: If true, indicates the session was repurposed (e.g., for a bug report) and the buffer is unavailable for dumping.
    *   **One-way**: Yes.

*   **`reportTrace(TraceReportParams params)`**:
    *   **Purpose**: Reports a captured trace to a specified service.
    *   **Arguments**:
        *   `params`: A `TraceReportParams` object containing details about the trace recipient and the trace file descriptor (fd).
    *   **One-way**: Yes.

## Java-to-C++ Translation Guide
*   **Binder Interface**: This is a standard AIDL interface. In C++, this corresponds to a `BnTracingServiceProxy` (native binder stub) or `BpTracingServiceProxy` (proxy).
*   **Implementation**: The server-side implementation resides in `system_server`.
