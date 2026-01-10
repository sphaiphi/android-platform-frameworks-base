# ImeTracker - Reverse Engineering Documentation

## Executive Summary
Interface and implementation for tracking IME visibility requests (show/hide) for debugging and metrics (Latency, Jank).

## Architecture
*   **Token**: Uses `Binder` tokens to track request lifecycles.
*   **Phases**: Defines phases of the show/hide flow (Client, Server, WM, IME).
*   **Loggers**: `ImeJankTracker`, `ImeLatencyTracker`.

## Java-to-C++ Translation Guide
*   **Telemetry**: Analytics/Tracing infrastructure.
