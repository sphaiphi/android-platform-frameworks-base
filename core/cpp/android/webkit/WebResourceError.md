# WebResourceError - Reverse Engineering Documentation

## Executive Summary
`WebResourceError` encapsulates error information (code and description) for resource loading failures.

## Detailed Functionality
*   **`getErrorCode()`**: Returns standard error constants (`ERROR_*`).
*   **`getDescription()`**: Returns a localized string description.

## Java-to-C++ Translation Guide
*   **Net Error**: Maps to network error codes (e.g., `net::ERR_CONNECTION_REFUSED`).
