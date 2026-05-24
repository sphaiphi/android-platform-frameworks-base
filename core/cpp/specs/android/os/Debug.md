# Debug - Reverse Engineering Documentation

## Executive Summary
`Debug` provides utilities for inspecting the Android Runtime (ART) and the Linux process. It includes APIs for memory stats (PSS, RSS), method tracing (`.trace` files), debugger control, and allocation counting.

## Architecture Overview
-   **Layer**: Bridge to VM and Kernel stats.
-   **Native Peer**: `VMDebug` (Dalvik/ART internal).
-   **MemoryInfo**: A nested static class `Debug.MemoryInfo` holding detailed memory breakdown (Dalvik, Native, Other, etc.).

## Detailed Functionality

### Memory Analysis
-   **`getMemoryInfo(MemoryInfo)`**: Populates the provided object with PSS/RSS/Dirty stats. Reads from `/proc/self/smaps` (native side).
-   **`getPss()`**: Quick total PSS.
-   **`dumpHprofData(String)`**: Dumps heap graph.

### Tracing
-   **`startMethodTracing()`**: Enables ART method profiling.
-   **`stopMethodTracing()`**: Stops profiling and flushes to disk.

### Debugger
-   **`waitForDebugger()`**: Blocks current thread until JDWP debugger attaches.
-   **`isDebuggerConnected()`**: Checks status.

## Java-to-C++ Translation Guide
-   **Equivalent**: `mallinfo` (libc), `/proc` parsing.
-   **Tracing**: Use `simpleperf` or `atrace` for native profiling. `Debug.startMethodTracing` is Java-specific.

## Implementation Risks
-   **Performance**: `getMemoryInfo` is expensive (reads/parses smaps). Do not call on critical paths.
