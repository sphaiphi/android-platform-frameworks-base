# IncorrectContextUseViolation - Reverse Engineering Documentation

## Executive Summary
`IncorrectContextUseViolation` is raised when a non-UI `Context` (like an `Application` context or a `Service` context) is used to perform UI-related operations, such as obtaining a `WindowManager` or inflating a layout that requires theme information.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Input**: Takes an `originStack` (Throwable) to point to the code that incorrectly accessed the context.

## Detailed Functionality
-   **Initialization**: The constructor uses `initCause(originStack)` to ensure the stack trace of the original misuse is preserved and reported.
