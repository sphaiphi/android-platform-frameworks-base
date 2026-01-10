# ServiceConnectionLeakedViolation - Reverse Engineering Documentation

## Executive Summary
`ServiceConnectionLeakedViolation` is raised when an `Activity` or component is destroyed while still bound to a `Service`. The binding must be explicitly unbinded to avoid leaks.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Reporting**: Captures the registration stack trace to help identify which `bindService` call was not matched with an `unbindService`.
