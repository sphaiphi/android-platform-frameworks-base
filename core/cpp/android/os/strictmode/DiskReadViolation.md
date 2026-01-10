# DiskReadViolation - Reverse Engineering Documentation

## Executive Summary
`DiskReadViolation` is one of the most common StrictMode violations. It is raised when a thread performing a disk read operation is part of a `ThreadPolicy` that forbids such operations (typically the UI thread).

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Policy**: Associated with `ThreadPolicy`.
-   **Detection**: Intercepted in `libcore` (POSIX `read`, etc.) and propagated up to Java.
