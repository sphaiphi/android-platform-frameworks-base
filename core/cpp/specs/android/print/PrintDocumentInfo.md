# PrintDocumentInfo - Reverse Engineering Documentation

## Executive Summary
`PrintDocumentInfo` describes the document being printed. It is created by the application during the `onLayout` phase and passed to the system. It contains metadata like the page count and content type.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Builder Pattern**: Uses inner `Builder` class.

## Detailed Functionality
-   **Page Count**: Can be a specific number or `PAGE_COUNT_UNKNOWN`.
-   **Content Type**: Document (optimized for text) or Photo (optimized for images).
-   **Data Size**: Optional estimate of the document size.

## Data Model
-   `mName`: String (document name)
-   `mPageCount`: int
-   `mContentType`: int
-   `mDataSize`: long

## Java-to-C++ Translation Guide
-   **Builder**: Replicate the builder pattern for easy construction.
-   **Parcelable**: Standard serialization.
