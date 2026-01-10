# CursorEntityIterator - Reverse Engineering Documentation

## Executive Summary
`CursorEntityIterator` is an abstract implementation of `EntityIterator` that wraps a `Cursor`. It iterates over entities where an entity might span multiple consecutive rows in the cursor (e.g., a contact with multiple phone numbers).

## Architecture Overview
-   **Inheritance:** Implements `EntityIterator`.
-   **Relationship:** Wraps `Cursor`.

## Detailed Functionality
-   **`next()`**: Checks if `hasNext()`, calls `getEntityAndIncrementCursor` to read the current entity and advance the cursor position.
-   **`getEntityAndIncrementCursor`** (Abstract): Must be implemented to read the entity from the current cursor position and move the cursor past it.

## Data Model
-   `mCursor`: `Cursor`.
-   `mIsClosed`: `boolean`.

## API Reference
-   `public boolean hasNext()`
-   `public Entity next()`
-   `public void close()`

## Java-to-C++ Translation Guide
-   **Iterator**: C++ iterators are different (begin/end). This behaves more like a Java Iterator or a C++ input iterator.

## Implementation Risks
-   **Cursor Position**: The subclass implementation of `getEntityAndIncrementCursor` MUST ensure the cursor is advanced, otherwise an infinite loop occurs.
