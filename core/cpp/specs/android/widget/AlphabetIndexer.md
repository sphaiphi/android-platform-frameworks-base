# AlphabetIndexer - Reverse Engineering Documentation

## Executive Summary
`AlphabetIndexer` is a helper class for adapters to implement `SectionIndexer`. It enables fast scrolling in lists sorted alphabetically (e.g., Contacts) by providing a mapping between alphabet letters and list positions.

## Architecture Overview
*   **Implements**: `SectionIndexer`, `DataSetObserver`.
*   **Dependencies**: `Cursor` (data source), `Collator` (string comparison).

## Detailed Functionality

### 1. Section Indexing
*   **`mAlphabet`**: A string containing the section headers (e.g., " ABC...Z").
*   **`mAlphaMap`**: A `SparseIntArray` cache mapping a letter (key) to a list position (value).

### 2. Binary Search (`getPositionForSection`)
*   Performs a binary search on the `Cursor` to find the first item starting with the requested letter.
*   Uses a `Collator` to compare the section letter with the data in the cursor's sorted column.
*   Optimized to linear scan if the search range is small.

## Java-to-C++ Translation Guide
*   **Collator**: Use `icu::Collator` or `std::locale` for locale-aware string comparison.
*   **Cursor Access**: Requires an abstraction for random-access data sources.

## Implementation Risks
*   **Cursor Performance**: Random access on SQLite cursors can be slow (window swapping). The binary search can trigger multiple window loads if not careful.
*   **Locale**: Sorting and indexing must respect the user's locale (e.g., accents).
