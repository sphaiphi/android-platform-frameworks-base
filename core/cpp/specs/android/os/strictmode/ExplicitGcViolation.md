# ExplicitGcViolation - Reverse Engineering Documentation

## Executive Summary
`ExplicitGcViolation` is raised when an application calls `System.gc()` or `Runtime.gc()`. Modern Android runtimes (ART) manage memory automatically, and explicit GC calls often indicate poor performance patterns or attempts to "fix" leaks that should be addressed differently.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Policy**: Associated with `ThreadPolicy`.
