# MetadataReader - Reverse Engineering Documentation

## Executive Summary
`MetadataReader` is a utility to extract metadata (specifically EXIF) from streams for `DocumentsProvider`.

## Architecture Overview
- **Role**: Helper.
- **Dependencies**: `ExifInterface`.

## Detailed Functionality
-   **MIME Types**: Checks for JPG/JPEG.
-   **Extraction**: Maps requested tags to `ExifInterface` attributes and bundles them.

## Java-to-C++ Translation Guide
-   **EXIF**: Use a C++ EXIF library (e.g., `libexif` or similar).
