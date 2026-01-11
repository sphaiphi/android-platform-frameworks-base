# SpanSet - Reverse Engineering Documentation

## Executive Summary
A caching structure to efficiently retrieve and iterate over spans of a specific type in a range. Avoids repeated `getSpans` calls.

## Data Model
- **`spans`**: Array of span objects.
- **`spanStarts`, `spanEnds`, `spanFlags`**: Parallel arrays.
- **`classType`**: The type of span being cached.

## API Reference
- **`init(Spanned, int start, int limit)`**: Fills the cache.
- **`getNextTransition(int start, int limit)`**: Finds next span boundary.

## Java-to-C++ Translation Guide
- **Optimization**: Critical for performance in `TextLine`. C++ can use vectors or pre-allocated buffers.
