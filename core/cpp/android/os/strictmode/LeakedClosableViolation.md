# LeakedClosableViolation - Reverse Engineering Documentation

## Executive Summary
`LeakedClosableViolation` is raised when a resource that implements `AutoCloseable` (like a `FileDescriptor`, `Cursor`, or `Socket`) is garbage collected without having been explicitly closed.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Detection**: Typically triggered by `Finalizer` or `Cleaner` hooks.

## Detailed Functionality
-   **Allocation Site**: The violation often includes an `allocationSite` (as the cause), which is a Throwable captured when the resource was first opened. This is essential for debugging where the leak originated.
