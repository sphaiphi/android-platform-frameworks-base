# PrintedPdfDocument - Reverse Engineering Documentation

## Executive Summary
`PrintedPdfDocument` is a helper class that extends `PdfDocument` to simplify the creation of PDF files for printing. It calculates page dimensions and content rectangles based on `PrintAttributes`, making it easier for apps to draw content correctly for a specific paper size and margins.

## Architecture Overview
- **Inheritance**: `PrintedPdfDocument` -> `PdfDocument`.
- **Role**: Helper / Utility.
- **Dependencies**: `PrintAttributes` (MediaSize, Margins).

## Detailed Functionality
-   **Dimension Calculation**: Converts `PrintAttributes` (mils) to PostScript points (1/72 inch).
-   **Page Creation**: `startPage(int)` creates a new page with the correct size and content rectangle already set up.
-   **Rectangle**: `getPageContentRect()` returns the drawable area inside the margins.

## Data Model
-   `mPageWidth`, `mPageHeight`: Page dimensions in points.
-   `mContentRect`: Content area `Rect`.

## API Reference
-   `startPage(int)`: Creates a page.
-   `getPageWidth()`, `getPageHeight()`, `getPageContentRect()`.

## Java-to-C++ Translation Guide
-   **Graphics**: This relies on `PdfDocument` (which wraps native Skia PDF generation). The C++ equivalent would interact directly with Skia or a similar PDF library.
-   **Unit Conversion**: Replicate the mils-to-points logic.
