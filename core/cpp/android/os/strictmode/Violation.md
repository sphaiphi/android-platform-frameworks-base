# Violation - Reverse Engineering Documentation

## Executive Summary
`Violation` is the abstract base class for all StrictMode violation types. It extends `Throwable` and provides custom hash code logic designed to facilitate the deduplication of violations. This allows the `StrictMode` system to avoid overwhelming the user or logs with identical reports for the same code path.

## Architecture Overview
-   **Inheritance**: Extends `java.lang.Throwable`.
-   **Role**: Root of the StrictMode violation hierarchy.
-   **Key Feature**: Deterministic identity based on the violation's content (message, stack trace, and cause).

## Detailed Functionality

### Identity & Deduplication (`hashCode`)
The class overrides `hashCode()` to provide a stable identifier for a specific instance of a violation.
-   **Components**: The hash is computed from:
    1.  The exception message (or class name if null).
    2.  The entire stack trace (via `calcStackTraceHashCode`).
    3.  The string representation of the cause (`Throwable.toString()`).
-   **Caching**: The hash code is cached in `mHashCode` and validated via `mHashCodeValid`.
-   **Invalidation**: The cache is reset (`mHashCodeValid = false`) whenever the state of the violation changes (e.g., calling `initCause`, `setStackTrace`, or `fillInStackTrace`).

### Stack Trace Hashing
`calcStackTraceHashCode` iterates through all `StackTraceElement`s and incorporates their individual hash codes into a combined result. This ensures that violations originating from different lines of code are treated as unique, even if they are of the same type.

## API Reference
-   `Violation(String message)`: Package-private constructor.
-   `hashCode()`: Overridden for stable identity.

## Java-to-C++ Translation Guide
-   **Relevance**: In a C++ port of StrictMode, a similar base class or struct would be needed to represent error reports.
-   **Hashing**: C++ `std::hash` or a custom combiner (like `boost::hash_combine`) should be used to replicate the deduplication logic.
-   **Stack Traces**: C++ equivalents (like `backtrace` or `std::stacktrace` in C++23) would be required to generate the identity hash.

## Implementation Risks
-   **Deduplication Collisions**: While unlikely, different stack traces could technically result in the same hash. The StrictMode system must decide if it relies solely on the hash for "seen" checks.
-   **Serialization**: `Violation` is a `Throwable`, which is `Serializable`. However, some subclasses (like `UnsafeIntentLaunchViolation`) contain non-serializable fields (`Intent`), which are marked `transient`.
