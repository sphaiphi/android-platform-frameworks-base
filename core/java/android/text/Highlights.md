# Highlights - Reverse Engineering Documentation

## Executive Summary
A data container for text highlights, associating ranges of text with `Paint` objects.

## Data Model
- **`mHighlights`**: List of Pairs `<Paint, int[]>`.
- `int[]` stores ranges as flattened `[start1, end1, start2, end2, ...]`.

## API Reference
- **`getSize()`**: Number of highlight groups.
- **`getPaint(int index)`**: Paint for the group.
- **`getRanges(int index)`**: Ranges for the group.

## Java-to-C++ Translation Guide
- **Struct**: `struct Highlight { Paint paint; std::vector<int> ranges; }`.
