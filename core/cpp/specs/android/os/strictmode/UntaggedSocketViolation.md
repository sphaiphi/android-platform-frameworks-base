# UntaggedSocketViolation - Reverse Engineering Documentation

## Executive Summary
`UntaggedSocketViolation` is raised when a network socket is created and used without being "tagged" via `TrafficStats`. Tagging allows the system to attribute network usage to specific components or tasks for better accounting and debugging.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Detection**: Hooked in the socket creation/connect logic in `libcore`.
