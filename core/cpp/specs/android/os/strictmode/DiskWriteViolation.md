# DiskWriteViolation - Reverse Engineering Documentation

## Executive Summary
`DiskWriteViolation` is raised when a thread attempts to write to disk while under a `ThreadPolicy` that prohibits it (e.g., the Main/UI thread).

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Policy**: Associated with `ThreadPolicy`.
