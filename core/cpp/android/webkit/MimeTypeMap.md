# MimeTypeMap - Reverse Engineering Documentation

## Executive Summary
`MimeTypeMap` provides a two-way mapping between file extensions and MIME types. It wraps the core `libcore.content.type.MimeMap`.

## Detailed Functionality
*   **`getFileExtensionFromUrl(url)`**: Extracts extension from a URL (stripping query/fragment).
*   **`getMimeTypeFromExtension(ext)`**: Extension -> MIME type.
*   **`getExtensionFromMimeType(mime)`**: MIME type -> Extension.
*   **`remapGenericMimeType`**: Logic to refine generic types like `application/octet-stream` based on file extension or content disposition.

## Java-to-C++ Translation Guide
*   **MIME Database**: Use a standard MIME type database (like shared-mime-info or hardcoded lists in the browser engine).
*   **Logic**: The `remapGenericMimeType` logic (sniffing) is common in browsers.
