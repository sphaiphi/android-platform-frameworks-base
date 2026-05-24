# DocumentsProvider - Reverse Engineering Documentation

## Executive Summary
`DocumentsProvider` is the base class for implementing a document provider for the Storage Access Framework (SAF).

## Architecture Overview
- **Inheritance**: `DocumentsProvider` -> `ContentProvider`.
- **Role**: Server-side implementation base.

## Detailed Functionality
-   **Method Dispatch**: Overrides `call()` to dispatch method names (`android:createDocument`, etc.) to abstract methods (`createDocument`, `openDocument`, etc.).
-   **Permissions**: Enforces `MANAGE_DOCUMENTS` permission and tree URI permissions.
-   **MIME Types**: Handles `openTypedAssetFile` by converting or checking MIME filters.

## API Reference
-   `queryRoots`, `queryChildDocuments`, `queryDocument`, `openDocument`.
-   `createDocument`, `renameDocument`, `deleteDocument`, `copyDocument`, `moveDocument`.

## Java-to-C++ Translation Guide
-   **ContentProvider**: If implementing a provider in C++, you need to handle the `IContentProvider` binder interface and implement the `call` method dispatch logic manually.
