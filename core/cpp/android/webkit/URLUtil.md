# URLUtil - Reverse Engineering Documentation

## Executive Summary
`URLUtil` provides static utility methods for validating, parsing, and guessing properties of URLs and file names.

## Detailed Functionality
*   **Validation**: `isValidUrl`, `isHttpUrl`, `isHttpsUrl`, `isAssetUrl`, `isFileUrl`, `isDataUrl`, `isContentUrl`.
*   **Helpers**: `stripAnchor`, `composeSearchUrl`, `decode` (hex).
*   **`guessFileName(url, contentDisposition, mimeType)`**:
    *   Complex logic to determine a filename for download.
    *   Parses `Content-Disposition` header (supports RFC 2616 and RFC 6266/RFC 5987 for encoded filenames).
    *   Falls back to URL path segments.
    *   Falls back to "downloadfile".
    *   Appends extension based on MimeType if missing.

## Java-to-C++ Translation Guide
*   **URL Parsing**: Use `GURL` or `std::filesystem` logic.
*   **Header Parsing**: Use a compliant HTTP header parser for Content-Disposition.
*   **MIME**: Integration with `MimeTypeMap`.
