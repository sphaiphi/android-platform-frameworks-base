# FileUriExposedViolation - Reverse Engineering Documentation

## Executive Summary
`FileUriExposedViolation` is raised when an application shares a `file://` URI with another application. This was deprecated in favor of `content://` URIs (using `FileProvider`) to improve security and ensure the receiving app has permission to access the file.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Context**: Security boundary check for cross-app IPC.
