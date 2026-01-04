# InstanceCountViolation - Reverse Engineering Documentation

## Executive Summary
`InstanceCountViolation` is a memory-leak detection violation. It is raised when the number of live instances of a specific class exceeds a developer-defined limit.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Detection**: Periodically checked by `StrictMode` during process idle or via specific hooks.

## Detailed Functionality
-   **Fake Stack Trace**: Unlike other violations, this class populates its stack trace with a "fake" entry: `android.os.StrictMode.setClassInstanceLimit`. This is because the violation is usually detected asynchronously, and the current stack trace is irrelevant; the information is about the global heap state.
-   **Data Model**: Stores the current instance count and the limit.

## API Reference
-   `getNumberOfInstances()`: Returns the count that triggered the violation.
