# WebViewDatabase - Reverse Engineering Documentation

## Executive Summary
`WebViewDatabase` allows managing stored data like autofill form data, saved passwords (legacy), and HTTP auth credentials.

## Detailed Functionality
*   **Http Auth**: `setHttpAuthUsernamePassword`, `getHttpAuthUsernamePassword`, `clearHttpAuthUsernamePassword`.
*   **Legacy**: `clearFormData`, `clearUsernamePassword` (Autofill is now handled by the system AutofillService).

## Java-to-C++ Translation Guide
*   **Database**: Maps to the browser's internal SQLite databases (Login Data, Web Data).
