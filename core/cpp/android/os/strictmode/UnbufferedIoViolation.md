# UnbufferedIoViolation - Reverse Engineering Documentation

## Executive Summary
`UnbufferedIoViolation` is raised when an application performs I/O operations without buffering (e.g., reading/writing one byte at a time to a file). This is extremely inefficient and can cause significant performance degradation.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Detection**: Typically hooked in `FileInputStream`/`FileOutputStream`.
