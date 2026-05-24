# ContextWrapper - Reverse Engineering Documentation

## Executive Summary
`ContextWrapper` is a proxy implementation of `Context` that delegates all calls to another `Context` (the base context). It allows subclassing to modify behavior without changing the original context.

## Architecture Overview
-   **Inheritance:** Extends `Context`.
-   **Pattern:** Decorator / Proxy.

## Detailed Functionality
-   **`attachBaseContext(Context base)`**: Sets the delegate. Can only be called once.
-   **Delegation**: All abstract methods of `Context` are implemented by calling `mBase.method()`.

## Data Model
-   `mBase`: `Context`.

## API Reference
-   All `Context` methods.

## Java-to-C++ Translation Guide
-   **Decorator**: Standard C++ pattern.

## Implementation Risks
-   **Recursion**: Ensure `mBase` is not `this` or a loop of wrappers.
