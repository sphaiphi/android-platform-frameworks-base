# SystemTextClassifier - Reverse Engineering Documentation

## Executive Summary
A `TextClassifier` implementation that proxies requests to the system `TextClassifierService` (via `ITextClassifierService` binder). It handles IPC and threading (waiting for callbacks via `BlockingCallback`).

## Architecture
*   **Proxy**: Calls `mManagerService`.
*   **Fallback**: Holds a local fallback classifier (usually NO_OP).
*   **Metadata**: Attaches `SystemTextClassifierMetadata` to requests.

## Java-to-C++ Translation Guide
*   **Binder**: Wraps `ITextClassifierService` calls.
*   **Synchronization**: Uses `CountDownLatch` to make async binder calls synchronous for the caller (if not on main thread).
