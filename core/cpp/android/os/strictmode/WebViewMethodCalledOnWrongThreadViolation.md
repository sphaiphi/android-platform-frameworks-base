# WebViewMethodCalledOnWrongThreadViolation - Reverse Engineering Documentation

## Executive Summary
`WebViewMethodCalledOnWrongThreadViolation` is raised when a `WebView` method is invoked from a thread other than the one where the `WebView` was created (usually the UI thread). `WebView` is not thread-safe.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Reporting**: Copies the stack trace from the point of the invalid call.
