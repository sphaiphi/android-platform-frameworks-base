# NetworkViolation - Reverse Engineering Documentation

## Executive Summary
`NetworkViolation` is raised when any network operation (socket connection, DNS lookup, etc.) is performed on a thread that prohibits it (usually the UI thread).

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Policy**: Associated with `ThreadPolicy`.
