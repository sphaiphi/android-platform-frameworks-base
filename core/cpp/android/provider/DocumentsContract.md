# DocumentsContract - Reverse Engineering Documentation

## Executive Summary
`DocumentsContract` defines the protocol for the Storage Access Framework (SAF). It specifies how `DocumentsProvider`s expose files and directories, and how clients (like the file picker) interact with them via `ContentResolver`.

## Architecture Overview
- **Authority**: Provider-specific.
- **Data Model**:
    -   **Roots**: Top-level entry points (SD card, Google Drive).
    -   **Documents**: Files or Directories (`MIME_TYPE_DIR`).
    -   **Tree**: Hierarchy of documents.

## Detailed Functionality
-   **URIs**:
    -   `buildRootsUri`: List roots.
    -   `buildDocumentUri`: Access a document.
    -   `buildTreeDocumentUri`: Access a tree.
-   **Columns**:
    -   `Document`: `COLUMN_DOCUMENT_ID`, `COLUMN_DISPLAY_NAME`, `COLUMN_MIME_TYPE`, `COLUMN_FLAGS`.
    -   `Root`: `COLUMN_ROOT_ID`, `COLUMN_TITLE`, `COLUMN_FLAGS`.
-   **Operations**: `createDocument`, `renameDocument`, `deleteDocument`, `copyDocument`, `moveDocument`. These are often implemented as `ContentResolver.call` methods.
-   **Thumbnail**: `getDocumentThumbnail`.

## API Reference
-   `build*Uri(...)` methods.
-   `createDocument`, `deleteDocument`, etc. (Wrappers around `ContentResolver.call`).
-   `isDocumentUri`, `isTreeUri`.

## Java-to-C++ Translation Guide
-   **Method Calls**: The "methods" (`android:createDocument`) are strings passed to the `call` method of the content provider. C++ clients must use the equivalent binder call for `IContentProvider::call`.
-   **Extras**: Arguments are passed in Bundles.
