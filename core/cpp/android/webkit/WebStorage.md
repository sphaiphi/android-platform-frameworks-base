# WebStorage - Reverse Engineering Documentation

## Executive Summary
`WebStorage` manages storage quotas and usage for the Web SQL Database and HTML5 Web Storage APIs.

## Detailed Functionality
*   **Origin**: Helper class to represent a storage origin (host/scheme/port).
*   **`getOrigins`**, **`getUsageForOrigin`**, **`getQuotaForOrigin`**: Async retrieval.
*   **`deleteOrigin`**, **`deleteAllData`**: Cleanup.

## Java-to-C++ Translation Guide
*   **Quota Manager**: Maps to the quota management system in the browser engine.
