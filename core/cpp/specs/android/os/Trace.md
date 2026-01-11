# Trace - Reverse Engineering Documentation

## Executive Summary
`Trace` provides the Java API for Android's system tracing mechanism (Systrace / Perfetto). It allows writing start/end events to the kernel trace buffer (`/sys/kernel/tracing/trace_marker`) via JNI.

## Architecture Overview
-   **Mechanism**: Writes string markers to the kernel `trace_marker` file.
-   **Tags**: 64-bit long bitmask (`TRACE_TAG_VIEW`, `TRACE_TAG_APP`, etc.) controls which categories are enabled.
-   **Optimization**: `isTagEnabled(long)` checks a volatile native variable (mapped via `SystemProperties` or shared memory) to avoid JNI overhead when tracing is off.

## API Reference
-   `traceBegin(long tag, String name)`: Starts a slice.
-   `traceEnd(long tag)`: Ends the most recent slice on the current thread.
-   `asyncTraceBegin`, `asyncTraceEnd`: Track events that span threads/time.
-   `traceCounter`: Integer counters.

## Java-to-C++ Translation Guide
-   **Equivalent**: `ATrace_*` NDK functions (`<trace.h>`).
-   **Macros**: `ATRACE_CALL()`, `ATRACE_BEGIN("name")`, `ATRACE_END()`.
-   **Implementation**: Both Java and C++ write to the same kernel file.

## Implementation Risks
-   **Overhead**: Writing to `trace_marker` has a cost. Checking `isTagEnabled` is critical.
-   **String Formatting**: Avoid complex string concatenation in the `traceBegin` call arguments to save CPU when tracing is off.
