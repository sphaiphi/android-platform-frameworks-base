# PageRange - Reverse Engineering Documentation

## Executive Summary
`PageRange` is a simple data class that represents a range of pages in a document. It is used throughout the printing framework to specify which pages should be printed or have been processed.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Scope**: Used by `PrintDocumentAdapter`, `PrintJobInfo`, and internal print services.

## Detailed Functionality
-   **Range Definition**: Defined by a `start` and `end` page index (both inclusive, zero-based).
-   **Validation**: Ensures `start >= 0`, `end >= 0`, and `start <= end`.
-   **Constants**: `ALL_PAGES` represents page 0 to `Integer.MAX_VALUE`.

## Data Model
-   `mStart`: int
-   `mEnd`: int

## API Reference
-   `getStart()`: Returns int.
-   `getEnd()`: Returns int.
-   `contains(int)`: Returns boolean.
-   `getSize()`: Returns int (number of pages in range).

## Java-to-C++ Translation Guide
-   **Struct**: Simple C++ struct.
-   **Parceling**: Standard integer read/write.
